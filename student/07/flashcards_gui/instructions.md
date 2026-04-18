# Flashcards GUI – Instructions

This program is a graphical flashcard application that allows the user to manage decks and study cards.

---

## GENERAL USAGE

1. Loading a file

- Enter the file name in the input field at the top.
- Press ENTER to load the file.
- The decks from the file will appear in the left panel.

2. Selecting a deck

- Click a deck from the "Decks" list.
- The cards of the selected deck are displayed in the table on the right.

---

## DECK MANAGEMENT

Add deck:

- Click "Add" under the deck list.
- Enter a deck name.
- Enter fields separated by semicolons (e.g. English;Finnish).
- Confirm to create the deck.

Remove deck:

- Select a deck.
- Click "Remove".
- A deck can only be removed if it contains no cards.

---

## CARD MANAGEMENT (Main page)

Add card:

- Select a deck.
- Click "New".
- Fill in at least one field.
- Confirm to add the card.

Edit card:

- Select a card in the table.
- Click "Edit".
- Modify the values and confirm.

Remove card:

- Select a card in the table.
- Click "Remove".

---

## STUDY MODE

Entering study mode:

- Select a deck.
- Click "Study".
- The deck must contain at least one card.

Study view:

- One card is shown at a time.
- The front and back fields can be selected from the dropdown menus.
- Click "Flip" to switch between front and back.
- Use "Previous" and "Next" to navigate between cards.
- The current position is shown as "current / total".

Add card (from study view):

- Click "Add card".
- Fill in the dialog and confirm.
- The card is added to the current deck and becomes immediately available.

Exit study mode:

- Click "Exit" to return to the main page.

---

## SPECIAL FEATURES

- The study widget is implemented as a custom widget derived from QWidget.
- It provides both studying functionality and the ability to add new cards.
- The front and back sides are visually distinguished using randomly selected colors.
- The currently visible side is highlighted with a colored border.

---

## ERROR HANDLING

The program includes input validation and error handling to prevent invalid operations.
For example:

- The user is warned if no deck or card is selected when required.
- Study mode cannot be entered if the deck has no cards.
- At least one field must be filled when adding or editing a card.
- Decks cannot be removed if they still contain cards.
- File loading errors are reported to the user.

All errors are shown using message dialogs to provide clear feedback.

## NOTES

- Study mode works even if the deck has only one field (the same field can be shown on both sides).
- At least one field must be filled when creating or editing a card.
- The program prevents removing decks that still contain cards.
