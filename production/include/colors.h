uint8_t percent(uint8_t percent) { return map(percent, 0, 100, 0, 255); }

DEFINE_GRADIENT_PALETTE(_orangePurpleBlue){
    percent(0),  239, 146, 58,  percent(12),  159, 85,  137,
    percent(24), 93,  47,  104, percent(38),  59,  106, 165,
    percent(45), 6,   53,  109, percent(55),  6,   53,  109,
    percent(100), 0, 100, 0};
    //percent(62), 59,  106, 165, percent(76),  93,  47,  104,
    //percent(88), 159, 85,  137, percent(100), 239, 146, 58};
CRGBPalette16 orangePurpleBlue = _orangePurpleBlue;

DEFINE_GRADIENT_PALETTE(_tealYellow){
    percent(0),  239, 146, 58,  percent(12),  240, 220, 0,
    percent(24), 180, 191, 21, percent(38),  59,  106, 165,
    percent(45), 6,   53,  109, percent(55),  6,   53,  109,
    percent(100), 0, 0, 100};
    //percent(62), 59,  106, 165, percent(76),  93,  47,  104,
    //percent(88), 159, 85,  137, percent(100), 239, 146, 58};
CRGBPalette16 tealYellow = _tealYellow;

DEFINE_GRADIENT_PALETTE(_fireAndIce){
    percent(0),  164, 29,  10,  percent(20),  235, 71,  15,
    percent(40), 250, 103, 29,  percent(60),  88,  139, 194,
    percent(80), 42,  82,  152, percent(100), 21,  31,  52};
CRGBPalette16 fireAndIce = _fireAndIce;

DEFINE_GRADIENT_PALETTE(_bluesAndPurples){
    percent(0),  123, 145, 204, percent(12),  65,  79,  134,
    percent(22), 158, 111, 245, percent(34),  142, 121, 223,
    percent(44), 86,  191, 253, percent(55),  0,0,0,
    percent(67), 82,  128, 244, percent(78),  193, 137, 244,
    percent(90), 65,  79,  134, percent(100), 123, 145, 204};
CRGBPalette16 bluesAndPurples = _bluesAndPurples;

DEFINE_GRADIENT_PALETTE(_rainbow){
    percent(0),  195, 8,   202, percent(10),  219, 9,   103,
    percent(19), 243, 56,  19,  percent(28),  248, 193, 26,
    percent(37), 139, 214, 8,   percent(46),  20,  229, 9,
    percent(55), 14,  234, 138, percent(64),  8,   184, 216,
    percent(73), 8,   55,  206, percent(82),  79,  9,   207,
    percent(91), 79,  9,   207, percent(100), 219, 9,   227};
CRGBPalette16 rainbow = _rainbow;

DEFINE_GRADIENT_PALETTE(_bluePurpleRedOrange){
    percent(0),  59,  57,  164, percent(18),  122, 88,  183,
    percent(32), 89,  45,  142, percent(44),  104, 28,  93,
    percent(59), 118, 23,  43,  percent(78),  221, 106, 62,
    percent(93), 236, 170, 86,  percent(100), 249, 234, 211};
CRGBPalette16 bluePurpleRedOrange = _bluePurpleRedOrange;

DEFINE_GRADIENT_PALETTE(_firePalette){
    //0,   139, 10,  0,  // dark red with hint of orange
    //127, 5, 0, 0,
    //255, 255, 150, 0}; // gold with hint of orange
    percent(0), 255, 230, 200, // basically white
    percent(25), 255, 150, 0, // gold with hint of orange
    percent(20), 255, 127, 0, // orange
    percent(50), 5, 0, 0, // basically black
    percent(70), 255, 0, 0, // red
    percent(100), 143, 3, 82}; // dark red/deep pink
CRGBPalette16 firePalette = _firePalette;

DEFINE_GRADIENT_PALETTE(_oceanPalette){
    0,   94, 255, 94,  // CHSV(HUE_GREEN, 100, 255)
    255, 15, 150, 15}; // greenish teal
CRGBPalette16 oceanPalette = _oceanPalette;

DEFINE_GRADIENT_PALETTE(_pinkBluePink){
    percent(0), 255, 40, 71, percent(50), 0, 0, 255, percent(100), 255, 40, 71};
CRGBPalette16 pinkBluePink = _pinkBluePink;

DEFINE_GRADIENT_PALETTE(_blueTealBlue){
    percent(0), 0, 0, 125, percent(50), 0, 250, 125, percent(100), 0, 0, 125};
CRGBPalette16 blueTealBlue = _blueTealBlue;

DEFINE_GRADIENT_PALETTE(_blueMagentaPurple){
    percent(0), 0, 0, 200, percent(50), 180, 24, 50, percent(100), 50, 0, 100};
CRGBPalette16 blueMagentaPurple = _blueMagentaPurple;

DEFINE_GRADIENT_PALETTE(_mintMagentaPurple){
    percent(0), 0, 255, 81, percent(50), 180, 24, 50, percent(100), 50, 0, 100};
CRGBPalette16 mintMagentaPurple = _mintMagentaPurple;

DEFINE_GRADIENT_PALETTE(_orangePinkMint){percent(0),   0,   255, 81,
                                         percent(50),  180, 24,  50,
                                         percent(100), 255, 100, 0};
CRGBPalette16 orangePinkMint = _orangePinkMint;

DEFINE_GRADIENT_PALETTE(_peacefulBlue){
    percent(0), 0, 0, 5, percent(50), 0, 0, 100, percent(100), 0, 0, 5};
CRGBPalette16 peacefulBlue = _peacefulBlue;

DEFINE_GRADIENT_PALETTE(_blueTealBlue2){
    percent(0), 0, 0, 100, percent(50), 0, 200, 75, percent(100), 0, 0, 100};
CRGBPalette16 blueTealBlue2 = _blueTealBlue2;

DEFINE_GRADIENT_PALETTE(_bluePurplePink){
    percent(0), 0, 0, 200, percent(50), 255, 50, 100, percent(100), 150, 0, 30};
CRGBPalette16 bluePurplePink = _bluePurplePink;

DEFINE_GRADIENT_PALETTE(_pinkWhiteOrange){
    percent(0), 100, 0, 20, percent(50), 40, 40, 40, percent(100), 100, 25, 0};
CRGBPalette16 pinkWhiteOrange = _pinkWhiteOrange;

DEFINE_GRADIENT_PALETTE(_yellowGreen){
    percent(0), 0, 50, 0, percent(30), 20, 100, 0, percent(100), 200, 250, 0};
CRGBPalette16 yellowGreen = _yellowGreen;

DEFINE_GRADIENT_PALETTE(_pinkCloudUpdate){percent(0),   255, 0, 0,
                                          percent(25),  236, 100, 153,
                                          percent(50),   30,  30,  226,
                                          percent(100), 100, 11, 191};
CRGBPalette16 pinkCloudUpdate = _pinkCloudUpdate;

DEFINE_GRADIENT_PALETTE(_redRoseLavendar){
    percent(0),   255, 0,   0,     // CRGB::Maroon
    percent(25),  200, 95, 20,    // CRGB::Chocolate
    percent(50), 255, 127, 80,    // CRGB::Coral
    percent(75), 230, 230, 250,
    percent(100), 0, 0, 0};  // CRGB::Lavender
CRGBPalette16 redRoseLavendar = _redRoseLavendar;

DEFINE_GRADIENT_PALETTE(_floralPalette){0,   255, 127, 80,   // CRGB::Coral
                                          255, 230, 230, 250}; // CRGB::Lavender
CRGBPalette16 floralPalette = _floralPalette;

// clang-format off
CRGBPalette16* activePalettes[] = {
  &orangePurpleBlue,
  &pinkCloudUpdate,
  &bluesAndPurples,
  &redRoseLavendar,
  &tealYellow,
  //&rainbow,
  //&bluePurpleRedOrange,
  //&firePalette,
  //&oceanPalette,
  //&pinkBluePink,
  //&blueTealBlue,
  //&blueMagentaPurple,
  //&mintMagentaPurple,
  //&peacefulBlue,
  //&blueTealBlue2,
  //&bluePurplePink,
  //&pinkWhiteOrange,
  //&yellowGreen,
  // TODO update NUM_PALETTES and palette IDs!
};
int NUM_PALETTES = sizeof(activePalettes) / sizeof(activePalettes[0]);
int activePaletteIndex = 0;
// clang-format on
