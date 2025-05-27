#ifndef MUSICPLAYERSYSTEM_H
#define MUSICPLAYERSYSTEM_H
#include "User.h"
#include "Admin.h"
#include <vector>
#include <string>
#include <algorithm>

class MusicPlayerSystem {
private:
    Admin admin;
    std::vector<User> users;
    User* currentUser;
    bool isAdminLoggedIn;

    void clearScreen() const;
    void displayMainMenu();
    void userLogin();
    void userRegister();
    void adminLogin();
    void userDashboard();
    void adminPanel();
    void playSongs();
    void managePlaylists();
    void manageFavorites();
    void searchSongs();
    void showArtists();
    void displaySongs(const std::vector<Song*>& songs) const;

public:
    MusicPlayerSystem();
    void run();
    void initializeSampleData();
};
#endif