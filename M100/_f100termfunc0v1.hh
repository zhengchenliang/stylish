#include <sys/ioctl.h>
#include <unistd.h>
#include <cmath>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <string>

namespace term
{

/* --------------------------------------------- Terminal Basics */

inline constexpr const char* CLF  = "\r\033[K";       // carrage return + clear
inline constexpr const char* CLR  = "\033[K";         // clear to end of line
inline constexpr const char* CLS  = "\033[2J\033[H";  // clear screen + home
inline constexpr const char* HOME = "\033[H";         // cursor home
inline constexpr const char* HIDE = "\033[?25l";      // hide cursor
inline constexpr const char* SHOW = "\033[?25h";      // show cursor

inline void move_(int _row, int _col)
{ // move cursor to (row, col) 1-indexed
  printf("\033[%d;%dH", _row, _col);
}

inline void clear_()
{ // clear screen and move home
  printf("%s", CLS);
  fflush(stdout);
}

inline std::pair<int, int> size_()
{ // get terminal (width, height)
  struct winsize w;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0)
  {
    return {w.ws_col, w.ws_row};
  }
  return {80, 24}; // fallback
}

inline void flush_() { fflush(stdout); }

/* --------------------------------------------- Base Styles */

inline constexpr const char* RST = "\033[0m";     // reset all
inline constexpr const char* BLD = "\033[1m";     // bold
inline constexpr const char* DIM = "\033[2m";     // dim
inline constexpr const char* UND = "\033[4m";     // underline
inline constexpr const char* BLK = "\033[5m";     // blink
inline constexpr const char* REV = "\033[7m";     // reverse

/* --------------------------------------------- Status Colors */

inline constexpr const char* OK  = "\033[38;2;48;209;88m";    // #30D158 success green
inline constexpr const char* WRN = "\033[38;2;255;159;10m";   // #FF9F0A warning orange
inline constexpr const char* ERR = "\033[38;2;255;69;58m";    // #FF453A error red
inline constexpr const char* INF = "\033[38;2;0;188;212m";    // #00BCD4 info cyan
inline constexpr const char* DBG = "\033[38;2;99;99;102m";    // #636366 debug gray

/* --------------------------------------------- Technical Grayscale L0-L9 */
// L0 (black) -> L5 (mid gray) -> L9 (white)

inline constexpr const char* L0 = "\033[38;2;18;18;20m";      // #121214 matte black
inline constexpr const char* L1 = "\033[38;2;28;28;30m";      // #1C1C1E panel dark
inline constexpr const char* L2 = "\033[38;2;44;44;46m";      // #2C2C2E panel light
inline constexpr const char* L3 = "\033[38;2;58;58;60m";      // #3A3A3C
inline constexpr const char* L4 = "\033[38;2;72;72;74m";      // #48484A steel gray
inline constexpr const char* L5 = "\033[38;2;99;99;102m";     // #636366 mid gray
inline constexpr const char* L6 = "\033[38;2;142;142;147m";   // #8E8E93
inline constexpr const char* L7 = "\033[38;2;174;174;178m";   // #AEAEB2 silver
inline constexpr const char* L8 = "\033[38;2;209;209;214m";   // #D1D1D6
inline constexpr const char* L9 = "\033[38;2;245;245;247m";   // #F5F5F7 white

// Background grayscale
inline constexpr const char* BG_L0 = "\033[48;2;18;18;20m";
inline constexpr const char* BG_L1 = "\033[48;2;28;28;30m";
inline constexpr const char* BG_L2 = "\033[48;2;44;44;46m";
inline constexpr const char* BG_L3 = "\033[48;2;58;58;60m";
inline constexpr const char* BG_L4 = "\033[48;2;72;72;74m";
inline constexpr const char* BG_L5 = "\033[48;2;99;99;102m";
inline constexpr const char* BG_L6 = "\033[48;2;142;142;147m";
inline constexpr const char* BG_L7 = "\033[48;2;174;174;178m";
inline constexpr const char* BG_L8 = "\033[48;2;209;209;214m";
inline constexpr const char* BG_L9 = "\033[48;2;245;245;247m";

// Grayscale heatmap for NONE style
inline constexpr const char* HEAT_GRAY[] = { L0, L1, L2, L3, L4, L5, L6, L7, L8, L9 };
inline constexpr const char* HEAT_GRAY_BG[] = { BG_L0, BG_L1, BG_L2, BG_L3, BG_L4, BG_L5, BG_L6, BG_L7, BG_L8, BG_L9 };

/* --------------------------------------------- Style Series */

namespace vers // vers empire color scheme
{

  // Crimson series (primary accent)
  inline constexpr const char* CRIMSON       = "\033[38;2;220;20;60m";    // #DC143C
  inline constexpr const char* CRIMSON_DARK  = "\033[38;2;139;0;0m";      // #8B0000
  inline constexpr const char* CRIMSON_GLOW  = "\033[38;2;255;69;100m";   // #FF4564
  inline constexpr const char* CRIMSON_FAINT = "\033[38;2;38;20;22m";     // #261416 (10%)

  // Gold series (highlights)
  inline constexpr const char* GOLD       = "\033[38;2;255;215;0m";       // #FFD700
  inline constexpr const char* GOLD_DARK  = "\033[38;2;184;134;11m";      // #B8860B
  inline constexpr const char* GOLD_LIGHT = "\033[38;2;255;236;139m";     // #FFEC8B

  // Background variants
  inline constexpr const char* BG_CRIMSON = "\033[48;2;139;0;0m";
  inline constexpr const char* BG_GOLD    = "\033[48;2;255;215;0m";

  // Text on backgrounds
  inline constexpr const char* TXT_ON_CRIMSON = "\033[38;2;255;236;139m"; // light gold
  inline constexpr const char* TXT_ON_GOLD    = "\033[38;2;18;18;20m";    // matte black

  // Semantic aliases
  inline constexpr const char* CMD = CRIMSON;       // command/prompt
  inline constexpr const char* HDR = GOLD;          // header/title
  inline constexpr const char* KEY = GOLD_LIGHT;    // key/label
  inline constexpr const char* VAL = CRIMSON_GLOW;  // value/number

  inline constexpr const char* PROMPT = "\033[38;2;220;20;60m>_<\033[0m "; // crimson ">_< "
  inline constexpr const size_t PRSIZ = 4; // visible width of prompt ">_< "

  // Heatmap gradient C0-C9 (Vers Empire: dark crimson -> crimson -> gold)
  inline constexpr const char* C0 = "\033[38;2;60;10;20m";       // #3C0A14 dark wine
  inline constexpr const char* C1 = "\033[38;2;100;15;30m";      // #640F1E deep crimson
  inline constexpr const char* C2 = "\033[38;2;139;0;0m";        // #8B0000 dark red
  inline constexpr const char* C3 = "\033[38;2;180;20;50m";      // #B41432 crimson
  inline constexpr const char* C4 = "\033[38;2;220;20;60m";      // #DC143C crimson bright
  inline constexpr const char* C5 = "\033[38;2;255;69;100m";     // #FF4564 crimson glow
  inline constexpr const char* C6 = "\033[38;2;255;150;50m";     // #FF9632 orange
  inline constexpr const char* C7 = "\033[38;2;255;180;0m";      // #FFB400 amber
  inline constexpr const char* C8 = "\033[38;2;255;215;0m";      // #FFD700 gold
  inline constexpr const char* C9 = "\033[38;2;255;236;139m";    // #FFEC8B gold light

  // Background heatmap gradient
  inline constexpr const char* BG_C0 = "\033[48;2;60;10;20m";
  inline constexpr const char* BG_C1 = "\033[48;2;100;15;30m";
  inline constexpr const char* BG_C2 = "\033[48;2;139;0;0m";
  inline constexpr const char* BG_C3 = "\033[48;2;180;20;50m";
  inline constexpr const char* BG_C4 = "\033[48;2;220;20;60m";
  inline constexpr const char* BG_C5 = "\033[48;2;255;69;100m";
  inline constexpr const char* BG_C6 = "\033[48;2;255;150;50m";
  inline constexpr const char* BG_C7 = "\033[48;2;255;180;0m";
  inline constexpr const char* BG_C8 = "\033[48;2;255;215;0m";
  inline constexpr const char* BG_C9 = "\033[48;2;255;236;139m";

  // Color array for programmatic access
  inline constexpr const char* HEAT_FG[] = { C0, C1, C2, C3, C4, C5, C6, C7, C8, C9 };
  inline constexpr const char* HEAT_BG[] = { BG_C0, BG_C1, BG_C2, BG_C3, BG_C4, BG_C5, BG_C6, BG_C7, BG_C8, BG_C9 };

} // namespace vers

namespace data // resident evil biohazard color scheme
{

  // Cyan series (technical/data)
  inline constexpr const char* CYAN       = "\033[38;2;0;188;212m";       // #00BCD4
  inline constexpr const char* CYAN_DARK  = "\033[38;2;0;131;143m";       // #00838F
  inline constexpr const char* CYAN_LIGHT = "\033[38;2;128;222;234m";     // #80DEEA
  inline constexpr const char* CYAN_FAINT = "\033[38;2;20;37;40m";        // #142528 (10%)

  // Green series (biohazard/warning)
  inline constexpr const char* GREEN       = "\033[38;2;76;175;80m";      // #4CAF50
  inline constexpr const char* GREEN_DARK  = "\033[38;2;27;94;32m";       // #1B5E20
  inline constexpr const char* GREEN_LIGHT = "\033[38;2;165;214;167m";    // #A5D6A7
  inline constexpr const char* GREEN_TOXIC = "\033[38;2;118;255;3m";      // #76FF03 toxic

  // Purple series (mutation/anomaly)
  inline constexpr const char* PURPLE       = "\033[38;2;156;39;176m";    // #9C27B0
  inline constexpr const char* PURPLE_DARK  = "\033[38;2;74;20;140m";     // #4A148C
  inline constexpr const char* PURPLE_LIGHT = "\033[38;2;206;147;216m";   // #CE93D8

  // Background variants
  inline constexpr const char* BG_CYAN   = "\033[48;2;0;188;212m";
  inline constexpr const char* BG_GREEN  = "\033[48;2;76;175;80m";
  inline constexpr const char* BG_PURPLE = "\033[48;2;156;39;176m";

  // Heatmap gradient C0-C9 (Resident Evil biohazard: dark teal -> cyan -> green -> toxic)
  // Smooth interpolation for continuous color transition
  inline constexpr const char* C0 = "\033[38;2;15;50;70m";       // #0F3246 dark teal
  inline constexpr const char* C1 = "\033[38;2;0;80;100m";       // #005064 deep teal
  inline constexpr const char* C2 = "\033[38;2;0;110;130m";      // #006E82 teal
  inline constexpr const char* C3 = "\033[38;2;0;140;150m";      // #008C96 cyan-teal
  inline constexpr const char* C4 = "\033[38;2;0;170;160m";      // #00AAA0 balanced cyan
  inline constexpr const char* C5 = "\033[38;2;0;195;130m";      // #00C382 cyan-green
  inline constexpr const char* C6 = "\033[38;2;40;215;90m";      // #28D75A green
  inline constexpr const char* C7 = "\033[38;2;100;235;50m";     // #64EB32 bright green
  inline constexpr const char* C8 = "\033[38;2;170;250;40m";     // #AAFA28 lime
  inline constexpr const char* C9 = "\033[38;2;240;255;80m";     // #F0FF50 toxic yellow

  // Background heatmap gradient
  inline constexpr const char* BG_C0 = "\033[48;2;15;50;70m";
  inline constexpr const char* BG_C1 = "\033[48;2;0;80;100m";
  inline constexpr const char* BG_C2 = "\033[48;2;0;110;130m";
  inline constexpr const char* BG_C3 = "\033[48;2;0;140;150m";
  inline constexpr const char* BG_C4 = "\033[48;2;0;170;160m";
  inline constexpr const char* BG_C5 = "\033[48;2;0;195;130m";
  inline constexpr const char* BG_C6 = "\033[48;2;40;215;90m";
  inline constexpr const char* BG_C7 = "\033[48;2;100;235;50m";
  inline constexpr const char* BG_C8 = "\033[48;2;170;250;40m";
  inline constexpr const char* BG_C9 = "\033[48;2;240;255;80m";

  // Semantic aliases
  inline constexpr const char* NUM = CYAN;          // numeric values
  inline constexpr const char* SYM = CYAN_LIGHT;    // symbol names
  inline constexpr const char* TIK = GREEN;         // tick data
  inline constexpr const char* HOT = GREEN_TOXIC;   // hot/active

  // Color array for programmatic access
  inline constexpr const char* HEAT_FG[] = { C0, C1, C2, C3, C4, C5, C6, C7, C8, C9 };
  inline constexpr const char* HEAT_BG[] = { BG_C0, BG_C1, BG_C2, BG_C3, BG_C4, BG_C5, BG_C6, BG_C7, BG_C8, BG_C9 };

} // namespace data

namespace chip // kakegurui gambling color scheme
{

  // Long/Buy series (pink/hot pink - Yumeko's lips)
  inline constexpr const char* LONG       = "\033[38;2;255;105;180m";     // #FF69B4 hot pink
  inline constexpr const char* LONG_DARK  = "\033[38;2;199;21;133m";      // #C71585 medium violet red
  inline constexpr const char* LONG_LIGHT = "\033[38;2;255;182;193m";     // #FFB6C1 light pink
  inline constexpr const char* LONG_GLOW  = "\033[38;2;255;20;147m";      // #FF1493 deep pink

  // Short/Sell series (sky blue - Kirari's eyes)
  inline constexpr const char* SHORT       = "\033[38;2;135;206;235m";    // #87CEEB sky blue
  inline constexpr const char* SHORT_DARK  = "\033[38;2;70;130;180m";     // #4682B4 steel blue
  inline constexpr const char* SHORT_LIGHT = "\033[38;2;176;224;230m";    // #B0E0E6 powder blue
  inline constexpr const char* SHORT_GLOW  = "\033[38;2;0;191;255m";      // #00BFFF deep sky blue

  // Background variants
  inline constexpr const char* BG_LONG  = "\033[48;2;255;105;180m";
  inline constexpr const char* BG_SHORT = "\033[48;2;135;206;235m";

  // Neutral series (for zero/flat positions)
  inline constexpr const char* FLAT       = "\033[38;2;192;192;192m";     // #C0C0C0 silver
  inline constexpr const char* FLAT_DARK  = "\033[38;2;128;128;128m";     // #808080 gray
  inline constexpr const char* FLAT_LIGHT = "\033[38;2;220;220;220m";     // #DCDCDC gainsboro

  // Jackpot series (gold chips - big wins)
  inline constexpr const char* JACKPOT       = "\033[38;2;255;215;0m";    // #FFD700 gold
  inline constexpr const char* JACKPOT_DARK  = "\033[38;2;218;165;32m";   // #DAA520 goldenrod
  inline constexpr const char* JACKPOT_LIGHT = "\033[38;2;255;255;224m";  // #FFFFE0 light yellow

  // Bust series (red chips - losses) - brighter for visibility
  inline constexpr const char* BUST       = "\033[38;2;255;99;71m";       // #FF6347 tomato (brighter)
  inline constexpr const char* BUST_DARK  = "\033[38;2;178;34;34m";       // #B22222 firebrick
  inline constexpr const char* BUST_LIGHT = "\033[38;2;255;160;122m";     // #FFA07A light salmon

  // Semantic aliases
  inline constexpr const char* BUY  = LONG;
  inline constexpr const char* SELL = SHORT;
  inline constexpr const char* WIN  = JACKPOT;
  inline constexpr const char* LOSS = BUST;
  inline constexpr const char* ZERO = FLAT;

  // Position gradient (short -> flat -> long)
  inline constexpr const char* POS_N2 = SHORT_GLOW;   // strong short
  inline constexpr const char* POS_N1 = SHORT;        // short
  inline constexpr const char* POS_0  = FLAT;         // flat
  inline constexpr const char* POS_P1 = LONG;         // long
  inline constexpr const char* POS_P2 = LONG_GLOW;    // strong long

  // Heatmap gradient C0-C9 (Kakegurui: Kirari ↔ Yumeko)
  // Symmetric brightness: dark edges, pale center (divergent colormap)
  // C0 = Kirari's icy stare, C9 = Yumeko's crimson fever
  inline constexpr const char* C0 = "\033[38;2;50;70;160m";      // #324699 Kirari's icy depths
  inline constexpr const char* C1 = "\033[38;2;70;100;195m";     // #4664C3 royal blue
  inline constexpr const char* C2 = "\033[38;2;100;135;220m";    // #6487DC azure
  inline constexpr const char* C3 = "\033[38;2;140;170;238m";    // #8CAAEE sky blue
  inline constexpr const char* C4 = "\033[38;2;180;195;245m";    // #B4C3F5 pale sky
  inline constexpr const char* C5 = "\033[38;2;240;185;200m";    // #F0B9C8 pale rose
  inline constexpr const char* C6 = "\033[38;2;250;155;175m";    // #FA9BAF rose
  inline constexpr const char* C7 = "\033[38;2;248;115;145m";    // #F87391 hot rose
  inline constexpr const char* C8 = "\033[38;2;235;70;110m";     // #EB466E deep pink
  inline constexpr const char* C9 = "\033[38;2;200;35;80m";      // #C82350 Yumeko's crimson eyes

  // Background heatmap gradient
  inline constexpr const char* BG_C0 = "\033[48;2;50;70;160m";
  inline constexpr const char* BG_C1 = "\033[48;2;70;100;195m";
  inline constexpr const char* BG_C2 = "\033[48;2;100;135;220m";
  inline constexpr const char* BG_C3 = "\033[48;2;140;170;238m";
  inline constexpr const char* BG_C4 = "\033[48;2;180;195;245m";
  inline constexpr const char* BG_C5 = "\033[48;2;240;185;200m";
  inline constexpr const char* BG_C6 = "\033[48;2;250;155;175m";
  inline constexpr const char* BG_C7 = "\033[48;2;248;115;145m";
  inline constexpr const char* BG_C8 = "\033[48;2;235;70;110m";
  inline constexpr const char* BG_C9 = "\033[48;2;200;35;80m";

  // Color array for programmatic access
  inline constexpr const char* HEAT_FG[] = { C0, C1, C2, C3, C4, C5, C6, C7, C8, C9 };
  inline constexpr const char* HEAT_BG[] = { BG_C0, BG_C1, BG_C2, BG_C3, BG_C4, BG_C5, BG_C6, BG_C7, BG_C8, BG_C9 };

} // namespace chip

/* --------------------------------------------- Style Enum */

enum class style_e : uint8_t
{
  NONE = 0, // grayscale L0-L9
  VERS = 1, // vers empire (crimson-gold)
  DATA = 2, // resident evil (cyan-green-toxic)
  CHIP = 3  // kakegurui (blue-pink)
};

inline int heat_idx_(double _ratio)
{ // map [0,1] ratio to heat index [0,9]
  if (_ratio <= 0.0) return 0;
  if (_ratio >= 1.0) return 9;
  return static_cast<int>(_ratio * 9.0);
}

inline const char* heat_fg_(double _ratio, style_e _style = style_e::DATA)
{ // get foreground color for heat value based on style
  int idx = heat_idx_(_ratio);
  switch (_style)
  {
    case style_e::VERS: return vers::HEAT_FG[idx];
    case style_e::DATA: return data::HEAT_FG[idx];
    case style_e::CHIP: return chip::HEAT_FG[idx];
    default:            return HEAT_GRAY[idx];
  }
}

inline const char* heat_bg_(double _ratio, style_e _style = style_e::DATA)
{ // get background color for heat value based on style
  int idx = heat_idx_(_ratio);
  switch (_style)
  {
    case style_e::VERS: return vers::HEAT_BG[idx];
    case style_e::DATA: return data::HEAT_BG[idx];
    case style_e::CHIP: return chip::HEAT_BG[idx];
    default:            return HEAT_GRAY_BG[idx];
  }
}

/* --------------------------------------------- Box Drawing (Unicode) */

inline constexpr const char* BOX_H  = "─";  // horizontal
inline constexpr const char* BOX_V  = "│";  // vertical
inline constexpr const char* BOX_TL = "┌";  // top-left
inline constexpr const char* BOX_TR = "┐";  // top-right
inline constexpr const char* BOX_BL = "└";  // bottom-left
inline constexpr const char* BOX_BR = "┘";  // bottom-right
inline constexpr const char* BOX_LT = "├";  // left-T
inline constexpr const char* BOX_RT = "┤";  // right-T
inline constexpr const char* BOX_TT = "┬";  // top-T
inline constexpr const char* BOX_BT = "┴";  // bottom-T
inline constexpr const char* BOX_X  = "┼";  // cross

// Double-line box
inline constexpr const char* BOX2_H  = "═";
inline constexpr const char* BOX2_V  = "║";
inline constexpr const char* BOX2_TL = "╔";
inline constexpr const char* BOX2_TR = "╗";
inline constexpr const char* BOX2_BL = "╚";
inline constexpr const char* BOX2_BR = "╝";

inline void box_(int _row, int _col, int _width, int _height, const char* _color = NULL)
{ // draw box at position with size, optional color
  if (_width < 2 || _height < 2) return;
  if (_color) printf("%s", _color);
  // top edge
  move_(_row, _col);
  printf("%s", BOX_TL);
  for (int i = 0; i < _width - 2; ++i) printf("%s", BOX_H);
  printf("%s", BOX_TR);
  // sides
  for (int r = 1; r < _height - 1; ++r)
  {
    move_(_row + r, _col);
    printf("%s", BOX_V);
    move_(_row + r, _col + _width - 1);
    printf("%s", BOX_V);
  }
  // bottom edge
  move_(_row + _height - 1, _col);
  printf("%s", BOX_BL);
  for (int i = 0; i < _width - 2; ++i) printf("%s", BOX_H);
  printf("%s", BOX_BR);
  if (_color) printf("%s", RST);
}

inline void hline_(int _row, int _col, int _width, const char* _color = NULL)
{ // draw horizontal line with optional color
  if (_color) printf("%s", _color);
  move_(_row, _col);
  for (int i = 0; i < _width; ++i) printf("%s", BOX_H);
  if (_color) printf("%s", RST);
}

inline void vline_(int _row, int _col, int _height, const char* _color = NULL)
{ // draw vertical line with optional color
  if (_color) printf("%s", _color);
  for (int i = 0; i < _height; ++i)
  {
    move_(_row + i, _col);
    printf("%s", BOX_V);
  }
  if (_color) printf("%s", RST);
}

/* --------------------------------------------- Bar Characters */

inline constexpr const char* BAR_FULL  = "█";
inline constexpr const char* BAR_7_8   = "▉";
inline constexpr const char* BAR_3_4   = "▊";
inline constexpr const char* BAR_5_8   = "▋";
inline constexpr const char* BAR_1_2   = "▌";
inline constexpr const char* BAR_3_8   = "▍";
inline constexpr const char* BAR_1_4   = "▎";
inline constexpr const char* BAR_1_8   = "▏";
inline constexpr const char* BAR_EMPTY = " ";

// Bar selection array for sub-character precision
inline constexpr const char* BAR_CHARS[] = {
  " ", "▏", "▎", "▍", "▌", "▋", "▊", "▉", "█"
};

inline void bar_(char* _buf, size_t _buflen, double _ratio, int _width) // 1D bar rendering
{ // render ASCII bar to buffer
  if (_width <= 0 || _buflen < (size_t)(_width * 3 + 1))
  {
    _buf[0] = '\0';
    return;
  }
  if (_ratio < 0.0) _ratio = 0.0;
  if (_ratio > 1.0) _ratio = 1.0;
  double full_blocks = _ratio * _width;
  int n_full = static_cast<int>(full_blocks);
  int partial = static_cast<int>((full_blocks - n_full) * 8.0);
  char* p = _buf;
  for (int i = 0; i < n_full && i < _width; ++i)
  {
    const char* b = BAR_FULL;
    while (*b) *p++ = *b++;
  }
  if (n_full < _width && partial > 0)
  {
    const char* b = BAR_CHARS[partial];
    while (*b) *p++ = *b++;
    n_full++;
  }
  for (int i = n_full; i < _width; ++i)
  {
    *p++ = ' ';
  }
  *p = '\0';
}

inline std::string bar_(double _ratio, int _width)
{ // render ASCII bar to string
  char buf[256];
  bar_(buf, sizeof(buf), _ratio, _width);
  return std::string(buf);
}

/* --------------------------------------------- Print Utilities */

inline void print_header_(const char* _text)
{ // header bar with vers-style background
  printf("%s%s%s %s %s\n", vers::BG_CRIMSON, BLD, vers::TXT_ON_CRIMSON, _text, RST);
}
inline void print_header_(std::string _text) { print_header_(_text.c_str()); }
inline void print_section_(const char* _text)
{ // section title in gold
  printf("%s%s%s %s\n", BLD, vers::GOLD, _text, RST);
}
inline void print_section_(std::string _text) { print_section_(_text.c_str()); }
inline void print_success_(const char* _msg)
{ // success message with green background label, green text
  printf("\033[48;2;48;209;88m\033[38;2;18;18;20m%s SUCCESS %s %s%s%s\n", BLD, RST, OK, _msg, RST);
}
inline void print_success_(std::string _msg) { print_success_(_msg.c_str()); }
inline void print_error_(const char* _msg)
{ // error message with red background label, red text
  printf("\033[48;2;255;69;58m\033[38;2;18;18;20m%s ERROR %s %s%s%s\n", BLD, RST, ERR, _msg, RST);
}
inline void print_error_(std::string _msg) { print_error_(_msg.c_str()); }
inline void print_warning_(const char* _msg)
{ // warning message with orange background label, orange text
  printf("\033[48;2;255;159;10m\033[38;2;18;18;20m%s WARNING %s %s%s%s\n", BLD, RST, WRN, _msg, RST);
}
inline void print_warning_(std::string _msg) { print_warning_(_msg.c_str()); }
inline void print_info_(const char* _msg)
{ // info message with cyan background label, cyan text
  printf("\033[48;2;0;188;212m\033[38;2;18;18;20m%s INFO %s %s%s%s\n", BLD, RST, INF, _msg, RST);
}
inline void print_info_(std::string _msg) { print_info_(_msg.c_str()); }
inline void print_debug_(const char* _msg)
{ // debug message with silver background label, silver text (brighter for visibility)
  printf("\033[48;2;174;174;178m\033[38;2;18;18;20m%s DEBUG %s %s%s%s\n", BLD, RST, L7, _msg, RST);
}
inline void print_debug_(std::string _msg) { print_debug_(_msg.c_str()); }

inline void print_separator_(const char* _color = L5)
{ // horizontal line separator
  printf("%s─────────────────────────────────────────────%s\n", _color, RST);
}
inline void print_status_(const char* _label, const char* _value, const char* _color = INF)
{ // status line: label = value
  printf("  %s%-16s%s %s%s%s\n", L7, _label, RST, _color, _value, RST);
}

// append styled output to string instead of printing
inline void print_header_(std::string& _out, const char* _text)
{
  _out += vers::BG_CRIMSON;
  _out += BLD;
  _out += vers::TXT_ON_CRIMSON;
  _out += " ";
  _out += _text;
  _out += " ";
  _out += RST;
  _out += "\n";
}
inline void print_section_(std::string& _out, const char* _text)
{
  _out += BLD;
  _out += vers::GOLD;
  _out += _text;
  _out += " ";
  _out += RST;
  _out += "\n";
}
inline void print_success_(std::string& _out, const char* _msg)
{
  _out += "\033[48;2;48;209;88m\033[38;2;18;18;20m";
  _out += BLD;
  _out += " SUCCESS ";
  _out += RST;
  _out += " ";
  _out += OK;
  _out += _msg;
  _out += RST;
  _out += "\n";
}
inline void print_error_(std::string& _out, const char* _msg)
{
  _out += "\033[48;2;255;69;58m\033[38;2;18;18;20m";
  _out += BLD;
  _out += " ERROR ";
  _out += RST;
  _out += " ";
  _out += ERR;
  _out += _msg;
  _out += RST;
  _out += "\n";
}
inline void print_warning_(std::string& _out, const char* _msg)
{
  _out += "\033[48;2;255;159;10m\033[38;2;18;18;20m";
  _out += BLD;
  _out += " WARNING ";
  _out += RST;
  _out += " ";
  _out += WRN;
  _out += _msg;
  _out += RST;
  _out += "\n";
}
inline void print_info_(std::string& _out, const char* _msg)
{
  _out += "\033[48;2;0;188;212m\033[38;2;18;18;20m";
  _out += BLD;
  _out += " INFO ";
  _out += RST;
  _out += " ";
  _out += INF;
  _out += _msg;
  _out += RST;
  _out += "\n";
}
inline void print_debug_(std::string& _out, const char* _msg)
{
  _out += "\033[48;2;174;174;178m\033[38;2;18;18;20m";
  _out += BLD;
  _out += " DEBUG ";
  _out += RST;
  _out += " ";
  _out += L7;
  _out += _msg;
  _out += RST;
  _out += "\n";
}

inline void print_separator_(std::string& _out, const char* _color = L5)
{
  _out += _color;
  _out += "─────────────────────────────────────────────";
  _out += RST;
  _out += "\n";
}
inline void print_status_(std::string& _out, const char* _label, const char* _value, const char* _color = INF)
{
  _out += "  ";
  _out += L7;
  _out += _label;
  _out += RST;
  _out += " ";
  _out += _color;
  _out += _value;
  _out += RST;
  _out += "\n";
}

/* --------------------------------------------- Number Formatting */

inline std::string fmt_num_(double _val, int _precision = 2)
{ // format number with precision
  char buf[32];
  snprintf(buf, sizeof(buf), "%.*f", _precision, _val);
  return std::string(buf);
}

inline std::string fmt_sci_(double _val, int _precision = 2)
{ // format in scientific notation
  char buf[32];
  snprintf(buf, sizeof(buf), "%.*e", _precision, _val);
  return std::string(buf);
}

inline std::string fmt_auto_(double _val, int _width = 8)
{ // auto-format based on magnitude
  if (_val == 0.0) return "0";
  double abs_val = std::fabs(_val);
  if (abs_val >= 1e6 || abs_val < 1e-3)
  {
    char buf[32];
    snprintf(buf, sizeof(buf), "%.1e", _val);
    return std::string(buf);
  }
  else if (abs_val >= 1000)
  {
    char buf[32];
    snprintf(buf, sizeof(buf), "%.0f", _val);
    return std::string(buf);
  }
  else if (abs_val >= 1)
  {
    char buf[32];
    snprintf(buf, sizeof(buf), "%.2f", _val);
    return std::string(buf);
  }
  else
  {
    char buf[32];
    snprintf(buf, sizeof(buf), "%.4f", _val);
    return std::string(buf);
  }
}

/* --------------------------------------------- Scale Utilities */

inline double log_mid_(double _min, double _max)
{ // compute middle point in log scale
  if (_min <= 0 || _max <= 0) return (_min + _max) / 2.0;
  return std::exp((std::log(_min) + std::log(_max)) / 2.0);
}

inline double lin_mid_(double _min, double _max)
{ // compute middle point in linear scale
  return (_min + _max) / 2.0;
}

inline double scale_val_(double _val, double _min, double _max, uint8_t _scale)
{ // normalize value to [0,1] range based on scale mode
  // _scale: 0=linear, 1=log
  if (_max <= _min) return 0.0;
  if (_scale == 1 && _min > 0 && _max > 0 && _val > 0)
  {
    double log_min = std::log(_min);
    double log_max = std::log(_max);
    double log_val = std::log(_val);
    return (log_val - log_min) / (log_max - log_min);
  }
  return (_val - _min) / (_max - _min);
}

} // namespace term

/* --------------------------------------------- */