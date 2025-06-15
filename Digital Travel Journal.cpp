#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "Trip.h"
using namespace std;

Dynamic_array<Trip*> trips;

void mainMenuScreen();
void createTripScreen();
void viewTripsScreen();
void tripDetailsScreen(int index);
void tripNotesScreen(int index);

int main() {
    InitWindow(800, 600, "Digital Travel Journal");
    SetTargetFPS(60);

    mainMenuScreen();

    CloseWindow();
    return 0;
}

void mainMenuScreen() {
    bool exitMenu = false;

    Rectangle createTripBtn = { 100, 150, 200, 40 };
    Rectangle viewTripsBtn = { 100, 210, 200, 40 };
    Rectangle exitBtn = { 100, 270, 200, 40 };

    while (!exitMenu && !WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Welcome to Digital Travel Journal", 100, 50, 30, DARKGRAY);

        if (GuiButton(createTripBtn, "Create New Trip")) {
            createTripScreen();
        }

        if (GuiButton(viewTripsBtn, "View Trips")) {
            viewTripsScreen();
        }

        if (GuiButton(exitBtn, "Exit")) {
            exitMenu = true;
        }

        EndDrawing();
    }
}

void createTripScreen() {
    static char title[64] = "";
    static char start[64] = "";
    static char end[64] = "";
    static char buddy[64] = "";

    static int statusIndex = 0;

    static bool titleEdit = false;
    static bool startEdit = false;
    static bool endEdit = false;
    static bool buddyEdit = false;

    Rectangle titleBox = { 100, 100, 200, 30 };
    Rectangle startBox = { 100, 140, 200, 30 };
    Rectangle endBox = { 100, 180, 200, 30 };
    Rectangle buddyBox = { 100, 220, 200, 30 };
    Rectangle statusBox = { 100, 260, 200, 30 };
    Rectangle addBtn = { 100, 310, 200, 40 };
    Rectangle backBtn = { 100, 370, 200, 40 };

    const char* statusOptions = "Completed;Current;Planned";

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Create New Trip", 100, 50, 30, DARKGRAY);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse = GetMousePosition();
            titleEdit = CheckCollisionPointRec(mouse, titleBox);
            startEdit = CheckCollisionPointRec(mouse, startBox);
            endEdit = CheckCollisionPointRec(mouse, endBox);
            buddyEdit = CheckCollisionPointRec(mouse, buddyBox);
        }

        GuiTextBox(titleBox, title, 64, titleEdit);
        GuiTextBox(startBox, start, 64, startEdit);
        GuiTextBox(endBox, end, 64, endEdit);
        GuiTextBox(buddyBox, buddy, 64, buddyEdit);
        GuiComboBox(statusBox, statusOptions, &statusIndex);

        if (GuiButton(addBtn, "Add Trip")) {
            std::string t = title;
            std::string s = start;
            std::string e = end;
            std::string b = buddy;
            TripStatus stat = static_cast<TripStatus>(statusIndex);
            trips.push(new Trip(t, s, e, b, stat));
            break;
        }

        if (GuiButton(backBtn, "Back")) {
            break;
        }

        EndDrawing();
    }
}
void viewTripsScreen() {
    bool exitView = false;

    Rectangle backBtn = { 600, 500, 150, 40 };

    while (!exitView && !WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("All Trips", 100, 30, 30, DARKGRAY);

        float y = 80;
        for (int i = 0; i < trips.size(); i++) {
            trips[i]->displayTripSummary(100, y);
            Rectangle tripBox = { 100, y, 600, 140 };
            if (CheckCollisionPointRec(GetMousePosition(), tripBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                tripDetailsScreen(i);
            }
            y += 150;
        }

        if (GuiButton(backBtn, "Back")) {
            exitView = true;
        }

        EndDrawing();
    }
}
void tripDetailsScreen(int index) {
    bool exitDetail = false;

    Rectangle notesBtn = { 100, 300, 250, 40 };
    Rectangle expensesBtn = { 100, 350, 250, 40 };
    Rectangle locationsBtn = { 100, 400, 250, 40 };
    Rectangle legsBtn = { 100, 450, 250, 40 };
    Rectangle backBtn = { 600, 500, 150, 40 };

    while (!exitDetail && !WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Trip Details", 100, 30, 30, DARKGRAY);

        trips[index]->displayTripSummary(100, 80);

        if (GuiButton(notesBtn, "View/Add Notes")) {
            tripNotesScreen(index);
        }
        if (GuiButton(expensesBtn, "View/Add Expenses")) {
            
        }
        if (GuiButton(locationsBtn, "View/Add Locations")) {
           
        }
        if (GuiButton(legsBtn, "View/Add Transport Legs")) {
            
        }

        if (GuiButton(backBtn, "Back")) {
            exitDetail = true;
        }

        EndDrawing();
    }
}

void tripNotesScreen(int index) {
    bool exit = false;

    static char title[64] = "";
    static char content[128] = "";
    static char date[32] = "";

    static bool titleEdit = false;
    static bool contentEdit = false;
    static bool dateEdit = false;

    Rectangle titleBox = { 100, 360, 300, 30 };
    Rectangle contentBox = { 100, 400, 300, 30 };
    Rectangle dateBox = { 100, 440, 300, 30 };
    Rectangle addBtn = { 100, 490, 200, 40 };
    Rectangle backBtn = { 600, 500, 150, 40 };

    while (!exit && !WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Notes", 100, 30, 30, DARKGRAY);

        Dynamic_array<Note*>& notes = trips[index]->getNotes();

        float y = 80;
        for (int i = 0; i < notes.size(); ++i) {
            Note* note = notes[i];
            DrawText(("• " + note->getTitle()).c_str(), 100, y, 20, DARKGRAY);
            DrawText(("  " + note->getDate()).c_str(), 120, y + 20, 18, GRAY);
            y += 50;
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 m = GetMousePosition();
            titleEdit = CheckCollisionPointRec(m, titleBox);
            contentEdit = CheckCollisionPointRec(m, contentBox);
            dateEdit = CheckCollisionPointRec(m, dateBox);
        }

        GuiTextBox(titleBox, title, 64, titleEdit);
        GuiTextBox(contentBox, content, 128, contentEdit);
        GuiTextBox(dateBox, date, 32, dateEdit);

        if (GuiButton(addBtn, "Add Note")) {
            std::string t = title;
            std::string c = content;
            std::string d = date;
            trips[index]->addNote(new Note(t, c, d));
            title[0] = '\0'; content[0] = '\0'; date[0] = '\0';
        }

        if (GuiButton(backBtn, "Back")) {
            exit = true;
        }

        EndDrawing();
    }
}
