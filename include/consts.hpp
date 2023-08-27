#pragma once
#include "pch.hpp"

constexpr SDL_Color KeyColor = {118, 66, 138, 255};
constexpr float Scale = 2;
inline std::string TilesheetName = "tilesheet";
constexpr int TilesheetCol = 7;
constexpr int TilesheetRow = 1;

enum class ImageTileType {
    Wall = 0,
    Pacman,
    PacmanEat,
    Bean,
    PowerBean,
    Ghost,
    GhostDoor,
};

// NOTE: edit your map here
// constexpr std::string_view MapDesc =
//     "WWWWWWWWWW"
//     "WBBBBBBBBW"
//     "WWBWGWBWWW"
//     "WPBWWWBWPW"
//     "WPBWWWBWPW"
//     "WWBBBBBBBW"
//     "WWBBBBBBBW"
//     "WWBBBBBBBW"
//     "WWBBBBBBBW"
//     "WWBBBBBBBW"
//     "WWBBBBBBBW"
//     "WWBBBBBBBW"
//     "WWWWWWWWWW";
// for dfs test
constexpr std::string_view MapDesc =
    "WWWWWWWWWW"
    "WBBBBBBBBW"
    "WWBWGWBWWW"
    "WPBWWWBWPW"
    "WPBWWWBWPW"
    "WWBBBBBBBW"
    "WWBBBBBBBW"
    "WWBBBBBWBW"
    "WWBBBWWWBW"
    "WWBBBWBBBW"
    "WWBBBBBBBW"
    "WWBBBBBBBW"
    "WWWWWWWWWW";
// constexpr std::string_view MapDesc =
// "WWWWW"
// "WBWWW"
// "WBBBW"
// "WBWBW"
// "WBBBW"
// "WBWWW"
// "WWWWW";

constexpr int MapWidth = 10;
constexpr int MapHeight = 13;

// constexpr int MapWidth = 5;
// constexpr int MapHeight = 7;