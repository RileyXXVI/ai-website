from typing import Optional
from sqlmodel import SQLModel, Field
from datetime import datetime

class User(SQLModel, table=True):
    id: Optional[int] = Field(default=None, primary_key=True)
    username: str = Field(index=True, unique=True)
    hashed_password: str
    created_at: datetime = Field(default_factory=datetime.utcnow)

class Message(SQLModel, table=True):
    id: Optional[int] = Field(default=None, primary_key=True)
    user_id: int = Field(index=True)
    character_prompt: Optional[str] = None
    role: str = "assistant"
    content: str
    created_at: datetime = Field(default_factory=datetime.utcnow)

class Character(SQLModel, table=True):
    id: Optional[int] = Field(default=None, primary_key=True)
    owner_id: int = Field(index=True)
    name: str
    prompt: str
    created_at: datetime = Field(default_factory=datetime.utcnow)

class Donation(SQLModel, table=True):
    id: Optional[int] = Field(default=None, primary_key=True)
    user_id: int = Field(index=True)
    character_id: int = Field(index=True)
    amount: float
    created_at: datetime = Field(default_factory=datetime.utcnow)