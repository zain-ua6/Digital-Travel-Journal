#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
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
void tripExpensesScreen(int index);
void tripLocationsScreen(int index);
void tripTransportLegsScreen(int index);

int main() {
    InitWindow(1200, 800, "Digital Travel Journal");
    SetTargetFPS(60);
    mainMenuScreen();

    for (int i = 0; i < trips.size(); ++i)
        delete trips[i];
    trips.clear();

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

        if (GuiButton(createTripBtn, "Create New Trip")) createTripScreen();
        if (GuiButton(viewTripsBtn, "View Trips")) viewTripsScreen();
        if (GuiButton(exitBtn, "Exit")) exitMenu = true;

        EndDrawing();
    }
}

void createTripScreen() {
    static char title[64] = "", start[64] = "", end[64] = "", buddy[64] = "";
    static int statusIndex = 0;
    static bool titleEdit = false, startEdit = false, endEdit = false, buddyEdit = false;
    const char* statusOptions = "Completed;Current;Planned";

    Rectangle titleBox = { 300, 100, 300, 30 };
    Rectangle startBox = { 300, 150, 300, 30 };
    Rectangle endBox = { 300, 200, 300, 30 };
    Rectangle buddyBox = { 300, 250, 300, 30 };
    Rectangle statusBox = { 300, 300, 300, 30 };
    Rectangle addBtn = { 100, 400, 200, 40 };
    Rectangle backBtn = { 100, 460, 200, 40 };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Create New Trip", 100, 30, 30, DARKGRAY);

        DrawText("Title:", 100, 105, 20, DARKGRAY);
        DrawText("Start Date:", 100, 155, 20, DARKGRAY);
        DrawText("End Date:", 100, 205, 20, DARKGRAY);
        DrawText("Travel Buddy:", 100, 255, 20, DARKGRAY);
        DrawText("Status:", 100, 305, 20, DARKGRAY);

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
            string t = title, s = start, e = end, b = buddy;
            TripStatus stat = static_cast<TripStatus>(statusIndex);
            trips.push(new Trip(t, s, e, b, stat));
            title[0] = start[0] = end[0] = buddy[0] = '\0'; statusIndex = 0;
            break;
        }

        if (GuiButton(backBtn, "Back")) break;
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

        if (GuiButton(backBtn, "Back")) exitView = true;
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

        if (GuiButton(notesBtn, "View/Add Notes")) tripNotesScreen(index);
        if (GuiButton(expensesBtn, "View/Add Expenses")) tripExpensesScreen(index);
        if (GuiButton(locationsBtn, "View/Add Locations")) tripLocationsScreen(index);
        if (GuiButton(legsBtn, "View/Add Transport Legs")) tripTransportLegsScreen(index);
        if (GuiButton(backBtn, "Back")) exitDetail = true;

        EndDrawing();
    }
}

void tripNotesScreen(int index) {
    bool exit = false;
    static char title[64] = "", content[128] = "", date[32] = "";
    static bool titleEdit = false, contentEdit = false, dateEdit = false;

    Rectangle titleBox = { 300, 360, 400, 30 };
    Rectangle contentBox = { 300, 410, 400, 30 };
    Rectangle dateBox = { 300, 460, 400, 30 };
    Rectangle addBtn = { 100, 520, 200, 40 };
    Rectangle backBtn = { 600, 520, 150, 40 };

    while (!exit && !WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Notes", 100, 30, 30, DARKGRAY);

        Dynamic_array<Note*>& notes = trips[index]->getNotes();
        float y = 80;
        for (int i = 0; i < notes.size(); ++i) {
            DrawText(("• " + notes[i]->getTitle()).c_str(), 100, y, 20, DARKGRAY);
            DrawText(("  " + notes[i]->getDate()).c_str(), 120, y + 20, 18, GRAY);
            y += 50;
        }

        DrawText("Title:", 100, 365, 20, DARKGRAY);
        DrawText("Content:", 100, 415, 20, DARKGRAY);
        DrawText("Date:", 100, 465, 20, DARKGRAY);

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
            string t = title, c = content, d = date;
            trips[index]->addNote(new Note(t, c, d));
            title[0] = content[0] = date[0] = '\0';
        }

        if (GuiButton(backBtn, "Back")) exit = true;
        EndDrawing();
    }
}

void tripExpensesScreen(int index) {
    bool exit = false;
    static char amount[16] = "", category[32] = "", description[64] = "", date[32] = "";
    static bool amountEdit = false, categoryEdit = false, descriptionEdit = false, dateEdit = false;

    Rectangle amountBox = { 300, 360, 300, 30 };
    Rectangle categoryBox = { 300, 410, 300, 30 };
    Rectangle descriptionBox = { 300, 460, 300, 30 };
    Rectangle dateBox = { 300, 510, 300, 30 };
    Rectangle addBtn = { 100, 570, 200, 40 };
    Rectangle backBtn = { 600, 570, 150, 40 };

    while (!exit && !WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Expenses", 100, 30, 30, DARKGRAY);

        Dynamic_array<Expense*>& expenses = trips[index]->getExpenses();
        float y = 80;
        for (int i = 0; i < expenses.size(); ++i) {
            Expense* exp = expenses[i];
            string line = "• " + exp->getCat() + " - $" + to_string(exp->getAmount());
            DrawText(line.c_str(), 100, y, 20, DARKGRAY);
            DrawText(exp->getDes().c_str(), 120, y + 20, 18, GRAY);
            DrawText(exp->getDate().c_str(), 120, y + 40, 18, LIGHTGRAY);
            y += 70;
        }

        DrawText("Amount:", 100, 365, 20, DARKGRAY);
        DrawText("Category:", 100, 415, 20, DARKGRAY);
        DrawText("Description:", 100, 465, 20, DARKGRAY);
        DrawText("Date:", 100, 515, 20, DARKGRAY);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 m = GetMousePosition();
            amountEdit = CheckCollisionPointRec(m, amountBox);
            categoryEdit = CheckCollisionPointRec(m, categoryBox);
            descriptionEdit = CheckCollisionPointRec(m, descriptionBox);
            dateEdit = CheckCollisionPointRec(m, dateBox);
        }

        GuiTextBox(amountBox, amount, 16, amountEdit);
        GuiTextBox(categoryBox, category, 32, categoryEdit);
        GuiTextBox(descriptionBox, description, 64, descriptionEdit);
        GuiTextBox(dateBox, date, 32, dateEdit);

        if (GuiButton(addBtn, "Add Expense")) {
            float a = atof(amount);
            string c = category, des = description, d = date;
            trips[index]->addExpense(new Expense(a, c, des, d));
            amount[0] = category[0] = description[0] = date[0] = '\0';
        }

        if (GuiButton(backBtn, "Back")) exit = true;
        EndDrawing();
    }
}
void tripLocationsScreen(int index) {
    bool exit = false;

    static char city[64] = "", country[64] = "", arrival[32] = "", departure[32] = "";
    static char weatherDesc[64] = "", tempStr[16] = "";
    static char activityName[64] = "", activityType[32] = "", activityDesc[64] = "", activityDate[32] = "";

    static bool cityEdit = false, countryEdit = false, arrivalEdit = false, departureEdit = false;
    static bool weatherEdit = false, tempEdit = false;
    static bool actNameEdit = false, actTypeEdit = false, actDescEdit = false, actDateEdit = false;

    Dynamic_array<Activity*> activities;

    Rectangle cityBox = { 200, 100, 250, 30 };
    Rectangle countryBox = { 200, 140, 250, 30 };
    Rectangle arrivalBox = { 200, 180, 250, 30 };
    Rectangle departureBox = { 200, 220, 250, 30 };
    Rectangle weatherBox = { 200, 260, 250, 30 };
    Rectangle tempBox = { 200, 300, 250, 30 };

    Rectangle actNameBox = { 200, 360, 250, 30 };
    Rectangle actTypeBox = { 200, 400, 250, 30 };
    Rectangle actDescBox = { 200, 440, 250, 30 };
    Rectangle actDateBox = { 200, 480, 250, 30 };
    Rectangle addActivityBtn = { 470, 480, 150, 30 };

    Rectangle addLocationBtn = { 200, 530, 250, 40 };
    Rectangle backBtn = { 600, 700, 150, 40 };

    while (!exit && !WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Add Location", 100, 30, 30, DARKGRAY);

        DrawText("City:", 100, 110, 20, DARKGRAY);
        DrawText("Country:", 100, 150, 20, DARKGRAY);
        DrawText("Arrival:", 100, 190, 20, DARKGRAY);
        DrawText("Departure:", 100, 230, 20, DARKGRAY);
        DrawText("Weather:", 100, 270, 20, DARKGRAY);
        DrawText("Temperature:", 100, 310, 20, DARKGRAY);

        DrawText("Add Activities:", 100, 340, 20, DARKGRAY);
        DrawText("Name:", 100, 370, 18, DARKGRAY);
        DrawText("Type:", 100, 410, 18, DARKGRAY);
        DrawText("Description:", 100, 450, 18, DARKGRAY);
        DrawText("Date:", 100, 490, 18, DARKGRAY);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 m = GetMousePosition();
            cityEdit = CheckCollisionPointRec(m, cityBox);
            countryEdit = CheckCollisionPointRec(m, countryBox);
            arrivalEdit = CheckCollisionPointRec(m, arrivalBox);
            departureEdit = CheckCollisionPointRec(m, departureBox);
            weatherEdit = CheckCollisionPointRec(m, weatherBox);
            tempEdit = CheckCollisionPointRec(m, tempBox);
            actNameEdit = CheckCollisionPointRec(m, actNameBox);
            actTypeEdit = CheckCollisionPointRec(m, actTypeBox);
            actDescEdit = CheckCollisionPointRec(m, actDescBox);
            actDateEdit = CheckCollisionPointRec(m, actDateBox);
        }

        GuiTextBox(cityBox, city, 64, cityEdit);
        GuiTextBox(countryBox, country, 64, countryEdit);
        GuiTextBox(arrivalBox, arrival, 32, arrivalEdit);
        GuiTextBox(departureBox, departure, 32, departureEdit);
        GuiTextBox(weatherBox, weatherDesc, 64, weatherEdit);
        GuiTextBox(tempBox, tempStr, 16, tempEdit);

        GuiTextBox(actNameBox, activityName, 64, actNameEdit);
        GuiTextBox(actTypeBox, activityType, 32, actTypeEdit);
        GuiTextBox(actDescBox, activityDesc, 64, actDescEdit);
        GuiTextBox(actDateBox, activityDate, 32, actDateEdit);

        if (GuiButton(addActivityBtn, "Add Activity")) {
            string name = activityName, type = activityType, desc = activityDesc, date = activityDate;
            activities.push(new Activity(name, type, desc, date));
            activityName[0] = activityType[0] = activityDesc[0] = activityDate[0] = '\0';
        }

        float y = 540;
        for (int i = 0; i < activities.size(); ++i) {
            string summary = "- " + activities[i]->getName() + " (" + activities[i]->getDate() + ")";
            DrawText(summary.c_str(), 480, y, 16, DARKGRAY);
            y += 20;
        }

        if (GuiButton(addLocationBtn, "Add Location")) {
            string c = city, co = country, arr = arrival, dep = departure, desc = weatherDesc;
            float temp = atof(tempStr);
            Weather w(desc, temp, desc);
            Location* loc = new Location(c, co, arr, dep, w);
            for (int i = 0; i < activities.size(); ++i)
                loc->addActivity(activities[i]);
            activities.clear();
            trips[index]->addLocation(loc);
            city[0] = country[0] = arrival[0] = departure[0] = weatherDesc[0] = tempStr[0] = '\0';
        }

        if (GuiButton(backBtn, "Back")) {
            for (int i = 0; i < activities.size(); ++i)
                delete activities[i];
            activities.clear();
            exit = true;
        }

        EndDrawing();
    }
}
void tripTransportLegsScreen(int index) {
    bool exit = false;

    static char mode[64] = "", from[64] = "", to[64] = "", date[32] = "", costStr[16] = "";
    static bool modeEdit = false, fromEdit = false, toEdit = false, dateEdit = false, costEdit = false;

    Rectangle modeBox = { 200, 100, 250, 30 };
    Rectangle fromBox = { 200, 150, 250, 30 };
    Rectangle toBox = { 200, 200, 250, 30 };
    Rectangle dateBox = { 200, 250, 250, 30 };
    Rectangle costBox = { 200, 300, 250, 30 };

    Rectangle addLegBtn = { 200, 360, 250, 40 };
    Rectangle backBtn = { 600, 500, 150, 40 };

    while (!exit && !WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Add Transport Leg", 100, 30, 30, DARKGRAY);
        DrawText("Mode:", 100, 110, 18, DARKGRAY);
        DrawText("From:", 100, 160, 18, DARKGRAY);
        DrawText("To:", 100, 210, 18, DARKGRAY);
        DrawText("Date:", 100, 260, 18, DARKGRAY);
        DrawText("Cost:", 100, 310, 18, DARKGRAY);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 m = GetMousePosition();
            modeEdit = CheckCollisionPointRec(m, modeBox);
            fromEdit = CheckCollisionPointRec(m, fromBox);
            toEdit = CheckCollisionPointRec(m, toBox);
            dateEdit = CheckCollisionPointRec(m, dateBox);
            costEdit = CheckCollisionPointRec(m, costBox);
        }

        GuiTextBox(modeBox, mode, 64, modeEdit);
        GuiTextBox(fromBox, from, 64, fromEdit);
        GuiTextBox(toBox, to, 64, toEdit);
        GuiTextBox(dateBox, date, 32, dateEdit);
        GuiTextBox(costBox, costStr, 16, costEdit);

        if (GuiButton(addLegBtn, "Add Transport Leg")) {
            string m = mode, f = from, t = to, d = date;
            float cost = atof(costStr);
            trips[index]->addTransportLeg(new TransportLeg(m, f, t, d, cost));
            mode[0] = from[0] = to[0] = date[0] = costStr[0] = '\0';
        }

        if (GuiButton(backBtn, "Back")) {
            exit = true;
        }

        EndDrawing();
    }
}