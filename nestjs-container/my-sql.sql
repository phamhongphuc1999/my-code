CREATE DATABASE simple_app;
GO

USE simple_app;
GO

CREATE TABLE Users (
  Id INT PRIMARY KEY AUTO_INCREMENT,
  Username VARCHAR(30) NOT NULL,
  Password VARCHAR(100) NOT NULL,
  Email VARCHAR(50) NOT NULL
);
GO

INSERT INTO Users (username, password, email)
VALUES ('user1', '$2b$10$C/isoTFnvi387Lj8k7UXWemekD.XhOcLQKq8C5QboDHrq8AUWZRGS', 'php@gmail.com'),
        ('user2', '$2b$10$C/isoTFnvi387Lj8k7UXWemekD.XhOcLQKq8C5QboDHrq8AUWZRGS', 'php1@gmail.com'),
        ('user3', '$2b$10$C/isoTFnvi387Lj8k7UXWemekD.XhOcLQKq8C5QboDHrq8AUWZRGS', 'php2@gmail.com'),
        ('user4', '$2b$10$C/isoTFnvi387Lj8k7UXWemekD.XhOcLQKq8C5QboDHrq8AUWZRGS', 'php3@gmail.com'),
        ('user5', '$2b$10$C/isoTFnvi387Lj8k7UXWemekD.XhOcLQKq8C5QboDHrq8AUWZRGS', 'php4@gmail.com'),
        ('user11', '123456789', 'php10@gmail.com');
GO

CREATE TABLE Productions (
    Id INT PRIMARY KEY AUTO_INCREMENT,
    Name VARCHAR(30) NOT NULL,
    Amount INT NOT NULL,
    UserId INT,
    FOREIGN KEY (UserId) REFERENCES Users(id)
);
GO

INSERT INTO Productions (name, amount, UserId)
VALUES ('production1', 100, 1),
        ('production2', 200, 2),
        ('production3', 1000, 3);