#include "Player.hpp"
void HumanPlayer::placeAllShips() {
    for (int i = 0; i < 5; i++) {
        bool placed = false;
        while (!placed) {
            this->getGrid()->printGrid();
            char rowChar;
            int col;
            char dirChar; 
            cout << "Place " << this->getShips(i)->getName() << " (Size " << this->getShips(i)->getSize() << "): ";
            cout << "Enter Row (A-J), Col (0-9), Orientation (H/V): ";
            cin >> rowChar >> col >> dirChar;

            // המרת אות למספר
            if (rowChar >= 'a' && rowChar <= 'j') rowChar -= 32;
            int row = rowChar - 'A';
            bool horizontal = (dirChar == 'H' || dirChar == 'h');

            // 1. בדיקת גבולות (grid.inBounds)
            if (this->getGrid()->inBounds(row, col, this->getShips(i)->getSize(), horizontal)) {
                
                // 2. בדיקת חפיפה (לולאה ידנית לבדיקת isTileOccupied)
                bool overlap = false;
                for (int j = 0; j < this->getShips(i)->getSize(); j++) {
                    int r = row + (horizontal ? 0 : j);
                    int c = col + (horizontal ? j : 0);
                    if (this->getGrid()->isTileOccupied(r, c)) {
                        overlap = true;
                        break;
                    }
                }

                if (!overlap) {
                    // טריק: נשמור את האינדקס של הספינה כתו ('0', '1'...)
                    // זה יעזור לנו אח"כ ב-makeMove לדעת במי פגענו
                    char symbol = '0' + i; 
                    
                    this->getGrid()->placeShip(row, col, this->getShips(i)->getSize(), horizontal, symbol);
                    placed = true;
                } else {
                    cout << "Error: Position occupied! Try again." << endl;
                }
            } else {
                cout << "Error: Out of bounds! Try again." << endl;
            }
        }
    }
    this->getGrid()->printGrid();
    cout << "All ships placed!" << endl;
}

// --- ביצוע מהלך (Human) ---
void HumanPlayer::makeMove(Player* opponent) {
    int row, col;
    char rowChar;
    bool validMove = false;

    cout << "\n--- " << this->getPlayerName() << "'s Turn to Attack ---" << endl;

    while (!validMove) {
        cout << "Enter Row (A-J) and Col (0-9) to attack: ";
        cin >> rowChar >> col;

        if (rowChar >= 'a' && rowChar <= 'j') rowChar -= 32;
        row = rowChar - 'A';

        // בדיקה שהקלט בגבולות
        if (row >= 0 && row < 10 && col >= 0 && col < 10) {
            validMove = true;
        } else {
            cout << "Invalid coordinates." << endl;
        }
    }

    // בודקים מה יש בלוח של היריב
    // משתמשים ב-getGrid() כדי למנוע שגיאת inaccessible
    char target = opponent->getGrid()->getCell(row, col);

    // אם זה לא מים ('~') ולא מקום שכבר ירו בו ('X' או 'M') -> פגענו בספינה!
    if (target != '~' && target != 'X' && target != 'M') {
        cout << "HIT!" << endl;
        
        // סימון פגיעה בלוח של היריב
        opponent->getGrid()->markHit(row, col);

        // מציאת הספינה הנכונה:
        // שמרנו את האינדקס כתו ('0'-'4'), אז נמיר חזרה למספר
        int shipIndex = target - '0';
        
        // קריאה לפונקציה takeHit של הספינה הספציפית
        opponent->getShips(shipIndex)->takeHit();

    } else if (target == '~') {
        cout << "MISS!" << endl;
        opponent->getGrid()->markMiss(row, col);
    } else {
        cout << "You already shot there!" << endl;
    }

    // הדפסת הלוחות כנדרש
    cout << "--- Opponent's Board (Status) ---" << endl;
    opponent->getGrid()->printOpponentView(); // ידפיס X ו-M

    cout << "--- Your Board ---" << endl;
    this->getGrid()->printGrid();
}