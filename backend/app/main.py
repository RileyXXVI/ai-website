from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
import os
import openai
from dotenv import load_dotenv

load_dotenv()
OPENAI_API_KEY = os.getenv('OPENAI_API_KEY')
if not OPENAI_API_KEY:
    raise RuntimeError('OPENAI_API_KEY not set in environment')
openai.api_key = OPENAI_API_KEY

app = FastAPI()

class ChatRequest(BaseModel):
    message: str
    character_prompt: str = "You are a helpful assistant."  # optional persona/system prompt

@app.post('/api/chat')
async def chat(req: ChatRequest):
    try:
        messages = [
            {"role": "system", "content": req.character_prompt},
            {"role": "user", "content": req.message},
        ]
        resp = openai.ChatCompletion.create(
            model='gpt-3.5-turbo',
            messages=messages,
            max_tokens=400,
            temperature=0.8,
        )
        text = resp['choices'][0]['message']['content']
        return {"reply": text}
    except openai.error.OpenAIError as e:
        raise HTTPException(status_code=500, detail=str(e))
