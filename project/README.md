# Player Lineup

**Player Lineup** is a full-stack web application that allows users to manage basketball teams, players, and their statistics. The application is designed to be intuitive and efficient for coaches, team managers, or basketball enthusiasts who want a centralized space to track and organize player information.

The app supports creating teams, adding and removing players, and logging detailed stats for each individual player. Everything is stored securely in a structured database, and the application provides a seamless interface for interacting with that data.

---

## 🏗️ Overview

Player Lineup combines modern web technologies to deliver a smooth, responsive experience both on the frontend and backend. The application uses a client-server architecture, where data flows through a RESTful API and is securely persisted in a relational database.

This project was built with the goal of making team and player management as straightforward and accessible as possible, without sacrificing performance or flexibility.

---

## 🚀 Features

- **User Accounts**: Users can sign up and log in securely.
- **Team Management**: Create, edit, and delete teams.
- **Player Management**: Add new players to a team, update their information, or remove them.
- **Stat Tracking**: Record player-specific statistics (e.g., points, assists, rebounds).
- **Clean UI**: Responsive and modern interface built with a focus on usability.
- **Scalable Backend**: Organized and efficient server logic designed for real-world use.
- **Data Persistence**: All player, team, and stat data is saved reliably in a structured database.

---

## ⚙️ Technologies Used

The project is divided into two main parts: the **frontend** and the **backend**, each using its own set of modern tools and technologies.

### Frontend

- **React**: JavaScript library for building interactive user interfaces.
- **Vite**: Fast build tool that speeds up development and builds.
- **Yarn**: Package manager used for handling project dependencies.
- **Cypress**: End-to-end testing framework for simulating real user interactions.

### Backend

- **Node.js**: JavaScript runtime for executing backend code.
- **Express**: Web application framework used to build the server and API.
- **Prisma**: Type-safe ORM used to interact with the MySQL database.
- **JWT (JSON Web Tokens)**: Used for secure user authentication.
- **Yarn**: Also used on the backend for managing dependencies and scripts.
- **Jest**: JavaScript testing framework used to validate backend logic.

### Database

- **MySQL**: A reliable, structured relational database used to store all application data.
- Hosted externally by my university's server.

---

---

## 📋 Example Use Cases

### 🏀 For Coaches and Team Managers

Imagine a local basketball coach named Emma. She wants to manage her team digitally instead of using messy spreadsheets or notes on paper. With Player Lineup:

1. Emma creates an account and logs in.
2. She sets up her basketball team, "The Golden Lions".
3. She adds her players with names and positions.
4. After each game, Emma logs player performance: points scored, assists, rebounds, and more.
5. Over time, she can analyze trends in player performance, make informed lineup decisions, and easily manage changes to her roster.

### 📊 For Basketball Fans

Jordan is a basketball fan who enjoys following players across different teams. He wants to compare how his favorite players perform throughout the season. Using Player Lineup:

1. Jordan creates an account and builds a few custom teams with players he follows closely, like "Rising Rookies" or "Top 3-Point Shooters".
2. He enters player stats after watching games or checking box scores: points, assists, steals and turnovers.
3. The app allows Jordan to view all the stats side by side and see how each player stacks up.
4. Over time, he starts noticing trends and keeps his list up to date, helping him make fantasy basketball decisions and fuel discussions with friends.

Whether you're managing a real basketball team or just tracking your favorite players, Player Lineup offers a flexible way to organize and analyze performance.

## 🔐 Security

- **Authentication** is handled using secure tokens to protect user sessions.
- Sensitive data like passwords is stored using hashing techniques to ensure privacy.
- The app separates environments for development and production to keep data secure and organized.

---

## 🧪 Testing

Testing is an important part of the project. The application includes:

- Automated **unit tests** to ensure key backend logic works correctly.
- **End-to-end tests** that simulate full user interactions to catch UI issues.
- Code coverage reports for maintaining code quality over time.

---

## 🎥 Video Demo

I created a video demo to showcase the main features of Player Lineup. You can watch it [here](https://youtu.be/92_4nfZErSA).

## 🤝 Contributions

Player Lineup is a learning-focused project and open to improvement. Whether you have ideas for features, want to clean up some UI, or suggest enhancements for future versions, your contributions are welcome and appreciated.

---

## 📄 License

This project was developed for educational purposes and is not currently licensed for commercial use.

---

Thanks for checking out Player Lineup!
