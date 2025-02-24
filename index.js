// server/index.js

const express = require('express');
const cors = require('cors');
const bodyParser = require('body-parser');
const axios = require('axios'); // For interacting with AI APIs

const app = express();
const PORT = 5000;

// Middleware
app.use(cors());
app.use(bodyParser.json());

// In-memory store for characters (replace with a database later)
const characters = [];

// API Route: Get all characters
app.get('/api/characters', (req, res) => {
    res.status(200).json(characters);
});

// API Route: Create a new character
app.post('/api/characters', (req, res) => {
    const { name, personality, backstory } = req.body;

    if (!name || !personality || !backstory) {
        return res.status(400).json({ error: 'All fields are required.' });
    }

    const newCharacter = { id: Date.now(), name, personality, backstory };
    characters.push(newCharacter);
    res.status(201).json(newCharacter);
});

// API Route: Delete a character
app.delete('/api/characters/:id', (req, res) => {
    const { id } = req.params;
    const index = characters.findIndex((char) => char.id === parseInt(id));

    if (index === -1) {
        return res.status(404).json({ error: 'Character not found.' });
    }

    characters.splice(index, 1);
    res.status(200).json({ message: 'Character deleted successfully.' });
});

// API Route for Chat
app.post('/api/chat', async (req, res) => {
    const { message, characterPrompt } = req.body;

    try {
        // Replace with OpenAI API or other AI API integration
        const response = await axios.post('https://api.openai.com/v1/chat/completions', {
            model: 'gpt-4',
            messages: [
                { role: 'system', content: characterPrompt },
                { role: 'user', content: message }
            ],
        }, {
            headers: {
                'Authorization': `Bearer YOUR_API_KEY`, // Replace with your API key
                'Content-Type': 'application/json'
            }
        });

        const reply = response.data.choices[0].message.content;
        res.status(200).json({ reply });

    } catch (error) {
        console.error('Error interacting with AI:', error);
        res.status(500).json({ error: 'Failed to fetch AI response.' });
    }
});

// Start Server
app.listen(PORT, () => {
    console.log(`Server running on http://localhost:${PORT}`);
});
// API Route for AI Chat
app.post('/api/chat', async (req, res) => {
    const { message, characterPrompt } = req.body;

    try {
        const response = await axios.post('https://api.openai.com/v1/chat/completions', {
            model: 'gpt-4',
            messages: [
                { role: 'system', content: characterPrompt },
                { role: 'user', content: message }
            ],
        }, {
            headers: {
                'Authorization': `Bearer YOUR_OPENAI_API_KEY`, // Replace with your OpenAI API Key
                'Content-Type': 'application/json'
            }
        });

        const reply = response.data.choices[0].message.content;
        res.status(200).json({ reply });

    } catch (error) {
        console.error('Error with AI Chat:', error);
        res.status(500).json({ error: 'Failed to fetch AI response.' });
    }
});

