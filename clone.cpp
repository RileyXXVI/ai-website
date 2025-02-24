<!-- character.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Character Manager</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <header>
        <h1>Character Manager</h1>
        <p>Create and manage your AI characters!</p>
    </header>

    <main>
        <section id="create-character">
            <h2>Create a New Character</h2>
            <form id="characterForm">
                <label for="name">Name:</label>
                <input type="text" id="name" name="name" required>

                <label for="personality">Personality:</label>
                <textarea id="personality" name="personality" rows="3" required></textarea>

                <label for="backstory">Backstory:</label>
                <textarea id="backstory" name="backstory" rows="4" required></textarea>

                <button type="submit">Create Character</button>
            </form>
        </section>

        <section id="character-list">
            <h2>Saved Characters</h2>
            <ul id="characters"></ul>
        </section>
    </main>

    <footer>
        <p>© 2025 Character Manager. All rights reserved.</p>
    </footer>

    <script>
        const apiUrl = 'http://localhost:5000/api/characters';

        // Fetch characters from the server
        async function fetchCharacters() {
            const response = await fetch(apiUrl);
            const characters = await response.json();

            const characterList = document.getElementById('characters');
            characterList.innerHTML = '';

            characters.forEach(character => {
                const li = document.createElement('li');
                li.textContent = `${character.name} - ${character.personality}`;
                const deleteButton = document.createElement('button');
                deleteButton.textContent = 'Delete';
                deleteButton.onclick = () => deleteCharacter(character.id);
                li.appendChild(deleteButton);
                characterList.appendChild(li);
            });
        }

        // Create a new character
        async function createCharacter(event) {
            event.preventDefault();
            const name = document.getElementById('name').value;
            const personality = document.getElementById('personality').value;
            const backstory = document.getElementById('backstory').value;

            await fetch(apiUrl, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({ name, personality, backstory }),
            });

            document.getElementById('characterForm').reset();
            fetchCharacters();
        }

        // Delete a character
        async function deleteCharacter(id) {
            await fetch(`${apiUrl}/${id}`, {
                method: 'DELETE',
            });
            fetchCharacters();
        }

        // Event listener for form submission
        document.getElementById('characterForm').addEventListener('submit', createCharacter);

        // Fetch characters on page load
        fetchCharacters();
    </script>
</body>
</html>
<section id="chat-box">
    <h2>Chat with Your Character</h2>
    <textarea id="userMessage" placeholder="Say something..."></textarea>
    <button onclick="sendMessage()">Send</button>
    <div id="chatHistory"></div>
</section>
<script>
    async function sendMessage() {
        const message = document.getElementById("userMessage").value;
        const characterPrompt = "Your character's personality goes here"; // Update dynamically if needed

        const response = await fetch('http://localhost:5000/api/chat', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ message, characterPrompt }),
        });

        const data = await response.json();
        const chatHistory = document.getElementById("chatHistory");
        chatHistory.innerHTML += `<p><strong>You:</strong> ${message}</p>`;
        chatHistory.innerHTML += `<p><strong>AI:</strong> ${data.reply}</p>`;
    }
</script>
const apiUrl = 'http://localhost:5000/api';
