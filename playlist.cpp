/*
 * ============================================================
 *   MUSIC PLAYLIST MANAGER
 *   Data Structure Used: DOUBLY LINKED LIST
 * ============================================================
 *
 * WHAT IS A DOUBLY LINKED LIST?
 * - A linked list where each node has TWO pointers:
 *     -> 'next' : points to the NEXT node
 *     -> 'prev' : points to the PREVIOUS node
 * - This lets us move both FORWARD and BACKWARD through the list.
 * - Perfect for a music playlist (next song / previous song)!
 *
 * NODE STRUCTURE:
 *
 *   NULL <- [prev | Song Data | next] <-> [prev | Song Data | next] -> NULL
 *            (head)                                                    (tail)
 *
 * ============================================================
 */

#include <iostream>
#include <string>
using namespace std;

// ============================================================
//  STEP 1: Define the Node
//  Each song in the playlist is stored in a "Node"
// ============================================================
struct Node {
    string title;    // Song title
    string artist;   // Artist name
    int duration;    // Duration in seconds

    Node* next;      // Pointer to NEXT song
    Node* prev;      // Pointer to PREVIOUS song

    // Constructor: sets up a new node with song details
    Node(string t, string a, int d) {
        title = t;
        artist = a;
        duration = d;
        next = NULL;
        prev = NULL;
    }
};

// ============================================================
//  STEP 2: Define the Playlist (Doubly Linked List)
// ============================================================
class Playlist {
private:
    Node* head;      // Points to the FIRST song
    Node* tail;      // Points to the LAST song
    Node* current;   // Points to the CURRENTLY PLAYING song
    int count;       // Total number of songs

public:
    // Constructor: initialize empty playlist
    Playlist() {
        head = NULL;
        tail = NULL;
        current = NULL;
        count = 0;
    }

    // ----------------------------------------------------------
    //  OPERATION 1: Add Song at END of playlist
    //  Time Complexity: O(1) - because we have a tail pointer
    // ----------------------------------------------------------
    void addSong(string title, string artist, int duration) {
        Node* newNode = new Node(title, artist, duration);

        if (head == NULL) {
            // List is empty: new node is both head and tail
            head = newNode;
            tail = newNode;
            current = newNode; // Auto-set as current if first song
        } else {
            // Link new node at the END
            newNode->prev = tail;   // New node's prev -> old tail
            tail->next = newNode;   // Old tail's next -> new node
            tail = newNode;         // Update tail to new node
        }

        count++;
        cout << "\n  [+] Added: \"" << title << "\" by " << artist << endl;
    }

    // ----------------------------------------------------------
    //  OPERATION 2: Delete a Song by Title
    //  Time Complexity: O(n) - we search through the list
    // ----------------------------------------------------------
    void deleteSong(string title) {
        if (head == NULL) {
            cout << "\n  [!] Playlist is empty!" << endl;
            return;
        }

        // Search for the node with matching title
        Node* temp = head;
        while (temp != NULL && temp->title != title) {
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "\n  [!] Song \"" << title << "\" not found!" << endl;
            return;
        }

        // --- Fix the links around this node ---

        if (temp->prev != NULL) {
            temp->prev->next = temp->next;  // Previous node skips over temp
        } else {
            head = temp->next;              // Deleting head: update head
        }

        if (temp->next != NULL) {
            temp->next->prev = temp->prev;  // Next node's prev skips over temp
        } else {
            tail = temp->prev;              // Deleting tail: update tail
        }

        // If the current song is deleted, move to next (or prev)
        if (current == temp) {
            if (temp->next != NULL) current = temp->next;
            else current = temp->prev;
        }

        cout << "\n  [-] Deleted: \"" << title << "\"" << endl;
        delete temp;  // Free memory
        count--;
    }

    // ----------------------------------------------------------
    //  OPERATION 3: Play Next Song
    // ----------------------------------------------------------
    void playNext() {
        if (current == NULL) {
            cout << "\n  [!] No song is playing!" << endl;
            return;
        }
        if (current->next == NULL) {
            cout << "\n  [!] This is the LAST song in the playlist!" << endl;
            return;
        }
        current = current->next;  // Move forward
        cout << "\n  [>>] Now Playing: \"" << current->title
             << "\" by " << current->artist << endl;
    }

    // ----------------------------------------------------------
    //  OPERATION 4: Play Previous Song
    // ----------------------------------------------------------
    void playPrev() {
        if (current == NULL) {
            cout << "\n  [!] No song is playing!" << endl;
            return;
        }
        if (current->prev == NULL) {
            cout << "\n  [!] This is the FIRST song in the playlist!" << endl;
            return;
        }
        current = current->prev;  // Move backward
        cout << "\n  [<<] Now Playing: \"" << current->title
             << "\" by " << current->artist << endl;
    }

    // ----------------------------------------------------------
    //  OPERATION 5: Display All Songs (Forward Traversal)
    //  Time Complexity: O(n)
    // ----------------------------------------------------------
    void displayForward() {
        if (head == NULL) {
            cout << "\n  [!] Playlist is empty!" << endl;
            return;
        }

        cout << "\n  ========================================" << endl;
        cout << "   PLAYLIST (Top to Bottom)" << endl;
        cout << "  ========================================" << endl;

        Node* temp = head;
        int index = 1;

        while (temp != NULL) {
            // Mark the currently playing song with a *
            if (temp == current)
                cout << "  * ";
            else
                cout << "    ";

            cout << index << ". " << temp->title
                 << " - " << temp->artist
                 << " [" << temp->duration / 60 << "m "
                 << temp->duration % 60 << "s]" << endl;

            temp = temp->next;
            index++;
        }

        cout << "  ========================================" << endl;
        cout << "  Total Songs: " << count << endl;
        if (current != NULL)
            cout << "  * Currently Playing: " << current->title << endl;
        cout << "  ========================================" << endl;
    }

    // ----------------------------------------------------------
    //  OPERATION 6: Display Songs in REVERSE (Backward Traversal)
    //  This shows the power of Doubly Linked List!
    // ----------------------------------------------------------
    void displayReverse() {
        if (tail == NULL) {
            cout << "\n  [!] Playlist is empty!" << endl;
            return;
        }

        cout << "\n  ========================================" << endl;
        cout << "   PLAYLIST (Bottom to Top)" << endl;
        cout << "  ========================================" << endl;

        Node* temp = tail;  // Start from TAIL (last song)
        int index = count;

        while (temp != NULL) {
            if (temp == current)
                cout << "  * ";
            else
                cout << "    ";

            cout << index << ". " << temp->title
                 << " - " << temp->artist << endl;

            temp = temp->prev;  // Move BACKWARD using prev pointer
            index--;
        }

        cout << "  ========================================" << endl;
    }

    // ----------------------------------------------------------
    //  OPERATION 7: Search for a Song
    //  Time Complexity: O(n)
    // ----------------------------------------------------------
    void searchSong(string title) {
        Node* temp = head;
        int pos = 1;

        while (temp != NULL) {
            if (temp->title == title) {
                cout << "\n  [Found] \"" << title << "\"" << endl;
                cout << "  Artist   : " << temp->artist << endl;
                cout << "  Duration : " << temp->duration / 60 << "m "
                     << temp->duration % 60 << "s" << endl;
                cout << "  Position : " << pos << " of " << count << endl;
                return;
            }
            temp = temp->next;
            pos++;
        }
        cout << "\n  [!] Song \"" << title << "\" not found!" << endl;
    }

    // ----------------------------------------------------------
    //  OPERATION 8: Play a specific song by title
    // ----------------------------------------------------------
    void playSong(string title) {
        Node* temp = head;
        while (temp != NULL) {
            if (temp->title == title) {
                current = temp;
                cout << "\n  [Play] Now Playing: \"" << current->title
                     << "\" by " << current->artist << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "\n  [!] Song \"" << title << "\" not found!" << endl;
    }

    // Destructor: Free all allocated memory
    ~Playlist() {
        Node* temp = head;
        while (temp != NULL) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
    }
};

// ============================================================
//  STEP 3: Main Function - Menu-driven program
// ============================================================
int main() {

    cout << "\n";
    cout << "  ============================================" << endl;
    cout << "      MUSIC PLAYLIST MANAGER" << endl;
    cout << "      (Using Doubly Linked List)" << endl;
    cout << "  ============================================" << endl;

    Playlist myPlaylist;
    int choice;
    string title, artist;
    int duration;

    do {
        cout << "\n  ---- MENU ----" << endl;
        cout << "  1. Add Song" << endl;
        cout << "  2. Delete Song" << endl;
        cout << "  3. Play Next Song" << endl;
        cout << "  4. Play Previous Song" << endl;
        cout << "  5. Display Playlist (Forward)" << endl;
        cout << "  6. Display Playlist (Reverse)" << endl;
        cout << "  7. Search Song" << endl;
        cout << "  8. Play a Specific Song" << endl;
        cout << "  0. Exit" << endl;
        cout << "\n  Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the newline from buffer

        switch (choice) {
            case 1:
                cout << "  Enter Song Title  : ";
                getline(cin, title);
                cout << "  Enter Artist Name : ";
                getline(cin, artist);
                cout << "  Enter Duration (in seconds): ";
                cin >> duration;
                myPlaylist.addSong(title, artist, duration);
                break;

            case 2:
                cout << "  Enter Song Title to Delete: ";
                getline(cin, title);
                myPlaylist.deleteSong(title);
                break;

            case 3:
                myPlaylist.playNext();
                break;

            case 4:
                myPlaylist.playPrev();
                break;

            case 5:
                myPlaylist.displayForward();
                break;

            case 6:
                myPlaylist.displayReverse();
                break;

            case 7:
                cout << "  Enter Song Title to Search: ";
                getline(cin, title);
                myPlaylist.searchSong(title);
                break;

            case 8:
                cout << "  Enter Song Title to Play: ";
                getline(cin, title);
                myPlaylist.playSong(title);
                break;

            case 0:
                cout << "\n  Goodbye! Keep listening to music!" << endl;
                break;

            default:
                cout << "\n  [!] Invalid choice! Please try again." << endl;
        }

    } while (choice != 0);

    return 0;
}
