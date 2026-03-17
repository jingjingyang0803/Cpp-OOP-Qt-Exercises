# Flashcards Program

This program implements a flashcard system that allows users to create, manage, and study decks of cards.

Each card contains multiple field definitions (e.g., translations between languages).

The program is controlled through a command-line interface (CLI).

## Features

The CLI supports the following commands:

- `file <file_name>` — Reads a deck from a file
- `decks` — Prints all decks
- `overview <deck_name>` — Prints all cards of a deck
- `study <deck_name>` — Studies cards of a deck
- `create <deck_name>` — Creates a new deck
- `copy <source_deck> <destination_deck>` — Copies the cards from the source deck into the destination deck
- `add_card <deck_name>` — Adds a new card to the deck
- `help` — Shows available commands
- `quit` — Terminates the program

## Program Structure

The program is divided into the following main classes:

- **Card** — Represents a single flashcard and stores field definitions.
- **Deck** — Stores a collection of cards and handles operations related to them.
- **DeckManager** — Manages all decks and acts as an interface between CLI and data.
- **Cli** — Handles user input and command parsing (provided template).
- **Utils** — Contains helper functions for field handling and string processing(provided template).

## Key Concepts

- Cards are identified by a unique ID.
- A card can belong to multiple decks.
- Decks enforce a specific set of fields.
- Cards are stored using smart pointers (`shared_ptr`).

## Study Mode

Users select:

- prompt fields
- answer fields

The program compares answers and calculates a score.

The final result is shown as a percentage.
