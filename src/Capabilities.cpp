/*
 * cpp-terminfo
 * C++ standalone library for terminal terminfo capabilities.
 *
 * SPDX-FileCopyrightText: 2023-2024 cpp-terminfo
 *
 * SPDX-License-Identifier: MIT
 */

#include "cpp-terminfo/Capabilities.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>

const std::array<Terminfo::Capability, Terminfo::Capabilities::m_booleans_size> Terminfo::Capabilities::m_booleans{
  // Booleans
  Capability{Boolean::auto_left_margin, "bw", "cub1 wraps from column 0 to last column"},
  Capability{Boolean::auto_right_margin, "am", "terminal has automatic margins"},
  Capability{Boolean::no_esc_ctlc, "xsb", "beehive (f1=escape, f2=ctrl C)"},
  Capability{Boolean::ceol_standout_glitch, "xhp", "standout not erased by overwriting (hp)"},
  Capability{Boolean::eat_newline_glitch, "xenl", "newline ignored after 80 cols (concept)"},
  Capability{Boolean::erase_overstrike, "eo", "can erase overstrikes with a blank"},
  Capability{Boolean::generic_type, "gn", "generic line type"},
  Capability{Boolean::hard_copy, "hc", "hardcopy terminal"},
  Capability{Boolean::has_meta_key, "km", "Has a meta key (i.e., sets 8th-bit)"},
  Capability{Boolean::has_status_line, "hs", "has extra status line"},
  Capability{Boolean::insert_null_glitch, "in", "insert mode distinguishes nulls"},
  Capability{Boolean::memory_above, "da", "display may be retained above the screen"},
  Capability{Boolean::memory_below, "db", "display may be retained below the screen"},
  Capability{Boolean::move_insert_mode, "mir", "safe to move while in insert mode"},
  Capability{Boolean::move_standout_mode, "msgr", "safe to move while in standout mode"},
  Capability{Boolean::over_strike, "os", "terminal can overstrike"},
  Capability{Boolean::status_line_esc_ok, "eslok", "escape can be used on the status line"},
  Capability{Boolean::dest_tabs_magic_smso, "xt", "tabs destructive, magic so char (t1061)"},
  Capability{Boolean::tilde_glitch, "hz", "cannot print ~'s (Hazeltine)"},
  Capability{Boolean::transparent_underline, "ul", "underline character overstrikes"},
  Capability{Boolean::xon_xoff, "xon", "terminal uses xon/xoff handshaking"},
  Capability{Boolean::needs_xon_xoff, "nxon", "padding will not work, xon/xoff required"},
  Capability{Boolean::prtr_silent, "mc5i", "printer will not echo on screen"},
  Capability{Boolean::hard_cursor, "chts", "cursor is hard to see"},
  Capability{Boolean::non_rev_rmcup, "nrrmc", "smcup does not reverse rmcup"},
  Capability{Boolean::no_pad_char, "npc", "pad character does not exist"},
  Capability{Boolean::non_dest_scroll_region, "ndscr", "scrolling region is non-destructive"},
  Capability{Boolean::can_change, "ccc", "terminal can re-define existing colors"},
  Capability{Boolean::back_color_erase, "bce", "screen erased with background color"},
  Capability{Boolean::hue_lightness_saturation, "hls", "terminal uses only HLS color notation (Tektronix)"},
  Capability{Boolean::col_addr_glitch, "xhpa", "only positive motion for hpa/mhpa caps"},
  Capability{Boolean::cr_cancels_micro_mode, "crxm", "using cr turns off micro mode"},
  Capability{Boolean::has_print_wheel, "daisy", "printer needs operator to change character set"},
  Capability{Boolean::row_addr_glitch, "xvpa", "only positive motion for vpa/mvpa caps"},
  Capability{Boolean::semi_auto_right_margin, "sam", "printing in last column causes cr"},
  Capability{Boolean::cpi_changes_res, "cpix", "changing character pitch changes resolution"},
  Capability{Boolean::lpi_changes_res, "lpix", "changing line pitch changes resolution"},
};

const std::array<Terminfo::Capability, Terminfo::Capabilities::m_intergers_size> Terminfo::Capabilities::m_integers{
  // Integers
  Capability{Integer::columns, "cols", "number of columns in a line"},
  Capability{Integer::init_tabs, "it", "tabs initially every # spaces"},
  Capability{Integer::lines, "lines", "number of lines on screen or page"},
  Capability{Integer::lines_of_memory, "lm", "lines of memory if > line. 0 means varies"},
  Capability{Integer::magic_cookie_glitch, "xmc", "number of blank characters left by smso or rmso"},
  Capability{Integer::padding_baud_rate, "pb", "lowest baud rate where padding needed"},
  Capability{Integer::virtual_terminal, "vt", "virtual terminal number (CB/unix)"},
  Capability{Integer::width_status_line, "wsl", "number of columns in status line"},
  Capability{Integer::num_labels, "nlab", "number of labels on screen"},
  Capability{Integer::label_height, "lh", "rows in each label"},
  Capability{Integer::label_width, "lw", "columns in each label"},
  Capability{Integer::max_attributes, "ma", "maximum combined attributes terminal can handle"},
  Capability{Integer::maximum_windows, "wnum", "maximum number of definable windows"},
  Capability{Integer::max_colors, "colors", "maximum number of colors on screen"},
  Capability{Integer::max_pairs, "pairs", "maximum number of color-pairs on the screen"},
  Capability{Integer::no_color_video, "ncv", "video attributes that cannot be used with colors"},
  Capability{Integer::buffer_capacity, "bufsz", "numbers of bytes buffered before printing"},
  Capability{Integer::dot_vert_spacing, "spinv", "spacing of pins vertically in pins per inch"},
  Capability{Integer::dot_horz_spacing, "spinh", "spacing of dots horizontally in dots per inch"},
  Capability{Integer::max_micro_address, "maddr", "maximum value in micro_..._address"},
  Capability{Integer::max_micro_jump, "mjump", "maximum value in parm_..._micro"},
  Capability{Integer::micro_col_size, "mcs", "character step size when in micro mode"},
  Capability{Integer::micro_line_size, "mls", "line step size when in micro mode"},
  Capability{Integer::number_of_pins, "npins", "numbers of pins in print-head"},
  Capability{Integer::output_res_char, "orc", "horizontal resolution in units per line"},
  Capability{Integer::output_res_line, "orl", "vertical resolution in units per line"},
  Capability{Integer::output_res_horz_inch, "orhi", "horizontal resolution in units per inch"},
  Capability{Integer::output_res_vert_inch, "orvi", "vertical resolution in units per inch"},
  Capability{Integer::print_rate, "cps", "print rate in characters per second"},
  Capability{Integer::wide_char_size, "widcs", "character step size when in double wide mode"},
  Capability{Integer::buttons, "btns", "number of buttons on mouse"},
  Capability{Integer::bit_image_entwining, "bitwin", "number of passes for each bit-image row"},
  Capability{Integer::bit_image_type, "bitype", "type of bit-image device"},
};

const std::array<Terminfo::Capability, Terminfo::Capabilities::m_strings_size> Terminfo::Capabilities::m_strings = {
  // Strings
  Capability{String::back_tab, "cbt", "back tab (P)"},
  Capability{String::bell, "bel", "audible signal (bell) (P)"},
  Capability{String::carriage_return, "cr", "carriage return (P*) (P*)"},
  Capability{String::change_scroll_region, "csr", "change region to line #1 to line #2 (P)"},
  Capability{String::clear_all_tabs, "tbc", "clear all tab stops (P)"},
  Capability{String::clear_screen, "clear", "clear screen and home cursor (P*)"},
  Capability{String::clr_eol, "el", "clear to end of line (P)"},
  Capability{String::clr_eos, "ed", "clear to end of screen (P*)"},
  Capability{String::column_address, "hpa", "horizontal position #1, absolute (P)"},
  Capability{String::command_character, "cmdch", "terminal settable cmd character in prototype !?"},
  Capability{String::cursor_address, "cup", "move to row #1 columns #2"},
  Capability{String::cursor_down, "cud1", "down one line"},
  Capability{String::cursor_home, "home", "home cursor (if no cup)"},
  Capability{String::cursor_invisible, "civis", "make cursor invisible"},
  Capability{String::cursor_left, "cub1", "move left one space"},
  Capability{String::cursor_mem_address, "mrcup", "memory relative cursor addressing, move to row #1 columns #2"},
  Capability{String::cursor_normal, "cnorm", "make cursor appear normal (undo civis/cvvis)"},
  Capability{String::cursor_right, "cuf1", "non-destructive space (move right one space)"},
  Capability{String::cursor_to_ll, "ll", "last line, first column (if no cup)"},
  Capability{String::cursor_up, "cuu1", "up one line"},
  Capability{String::cursor_visible, "cvvis", "make cursor very visible"},
  Capability{String::delete_character, "dch1", "delete character (P*)"},
  Capability{String::delete_line, "dl1", "delete line (P*)"},
  Capability{String::dis_status_line, "dsl", "disable status line"},
  Capability{String::down_half_line, "hd", "half a line down"},
  Capability{String::enter_alt_charset_mode, "smacs", "start alternate character set (P)"},
  Capability{String::enter_blink_mode, "blink", "turn on blinking"},
  Capability{String::enter_bold_mode, "bold", "turn on bold (extra bright) mode"},
  Capability{String::enter_ca_mode, "smcup", "string to start programs using cup"},
  Capability{String::enter_delete_mode, "smdc", "enter delete mode"},
  Capability{String::enter_dim_mode, "dim", "turn on half-bright mode"},
  Capability{String::enter_insert_mode, "smir", "enter insert mode"},
  Capability{String::enter_secure_mode, "invis", "turn on blank mode (characters invisible)"},
  Capability{String::enter_protected_mode, "prot", "turn on protected mode"},
  Capability{String::enter_reverse_mode, "rev", "turn on reverse video mode"},
  Capability{String::enter_standout_mode, "smso", "begin standout mode"},
  Capability{String::enter_underline_mode, "smul", "begin underline mode"},
  Capability{String::erase_chars, "ech", "erase #1 characters (P)"},
  Capability{String::exit_alt_charset_mode, "rmacs", "end alternate character set (P)"},
  Capability{String::exit_attribute_mode, "sgr0", "turn off all attributes"},
  Capability{String::exit_ca_mode, "rmcup", "strings to end programs using cup"},
  Capability{String::exit_delete_mode, "rmdc", "end delete mode"},
  Capability{String::exit_insert_mode, "rmir", "exit insert mode"},
  Capability{String::exit_standout_mode, "rmso", "exit standout mode"},
  Capability{String::exit_underline_mode, "rmul", "exit underline mode"},
  Capability{String::flash_screen, "flash", "visible bell (may not move cursor)"},
  Capability{String::form_feed, "ff", "hardcopy terminal page eject (P*)"},
  Capability{String::from_status_line, "fsl", "return from status line"},
  Capability{String::init_1string, "is1", "initialization string"},
  Capability{String::init_2string, "is2", "initialization string"},
  Capability{String::init_3string, "is3", "initialization string"},
  Capability{String::init_file, "if", "name of initialization file"},
  Capability{String::insert_character, "ich1", "insert character (P)"},
  Capability{String::insert_line, "il1", "insert line (P*)"},
  Capability{String::insert_padding, "ip", "insert padding after inserted character"},
  Capability{String::key_backspace, "kbs", "backspace key"},
  Capability{String::key_catab, "ktbc", "clear-all-tabs key"},
  Capability{String::key_clear, "kclr", "clear-screen or erase key"},
  Capability{String::key_ctab, "kctab", "clear-tab key"},
  Capability{String::key_dc, "kdch1", "delete-character key"},
  Capability{String::key_dl, "kdl1", "delete-line key"},
  Capability{String::key_down, "kcud1", "down-arrow key"},
  Capability{String::key_eic, "krmir", "sent by rmir or smir in insert mode"},
  Capability{String::key_eol, "kel", "clear-to-end-of-line key"},
  Capability{String::key_eos, "ked", "clear-to-end-of-screen key"},
  Capability{String::key_f0, "kf0", "F0 function key"},
  Capability{String::key_f1, "kf1", "F1 function key"},
  Capability{String::key_f10, "kf10", "F10 function key"},
  Capability{String::key_f2, "kf2", "F2 function key"},
  Capability{String::key_f3, "kf3", "F3 function key"},
  Capability{String::key_f4, "kf4", "F4 function key"},
  Capability{String::key_f5, "kf5", "F5 function key"},
  Capability{String::key_f6, "kf6", "F6 function key"},
  Capability{String::key_f7, "kf7", "F7 function key"},
  Capability{String::key_f8, "kf8", "F8 function key"},
  Capability{String::key_f9, "kf9", "F9 function key"},
  Capability{String::key_home, "khome", "home key"},
  Capability{String::key_ic, "kich1", "insert-character key"},
  Capability{String::key_il, "kil1", "insert-line key"},
  Capability{String::key_left, "kcub1", "left-arrow key"},
  Capability{String::key_ll, "kll", "lower-left key (home down)"},
  Capability{String::key_npage, "knp", "next-page key"},
  Capability{String::key_ppage, "kpp", "previous-page key"},
  Capability{String::key_right, "kcuf1", "right-arrow key"},
  Capability{String::key_sf, "kind", "scroll-forward key"},
  Capability{String::key_sr, "kri", "scroll-backward key"},
  Capability{String::key_stab, "khts", "set-tab key"},
  Capability{String::key_up, "kcuu1", "up-arrow key"},
  Capability{String::keypad_local, "rmkx", "leave keyboard transmit mode"},
  Capability{String::keypad_xmit, "smkx", "enter keyboard transmit mode"},
  Capability{String::lab_f0, "lf0", "label on function key f0 if not f0"},
  Capability{String::lab_f1, "lf1", "label on function key f1 if not f1"},
  Capability{String::lab_f10, "lf10", "label on function key f10 if not f10"},
  Capability{String::lab_f2, "lf2", "label on function key f2 if not f2"},
  Capability{String::lab_f3, "lf3", "label on function key f3 if not f3"},
  Capability{String::lab_f4, "lf4", "label on function key f4 if not f4"},
  Capability{String::lab_f5, "lf5", "label on function key f5 if not f5"},
  Capability{String::lab_f6, "lf6", "label on function key f6 if not f6"},
  Capability{String::lab_f7, "lf7", "label on function key f7 if not f7"},
  Capability{String::lab_f8, "lf8", "label on function key f8 if not f8"},
  Capability{String::lab_f9, "lf9", "label on function key f9 if not f9"},
  Capability{String::meta_off, "rmm", "turn off meta mode"},
  Capability{String::meta_on, "smm", "turn on meta mode (8th-bit on)"},
  Capability{String::newline, "nel", "newline (behave like cr followed by lf)"},
  Capability{String::pad_char, "pad", "padding char (instead of null)"},
  Capability{String::parm_dch, "dch", "delete #1 characters (P*)"},
  Capability{String::parm_delete_line, "dl", "delete #1 lines (P*)"},
  Capability{String::parm_down_cursor, "cud", "down #1 lines (P*)"},
  Capability{String::parm_ich, "ich", "insert #1 characters (P*)"},
  Capability{String::parm_index, "indn", "scroll forward #1 lines (P)"},
  Capability{String::parm_insert_line, "il", "insert #1 lines (P*)"},
  Capability{String::parm_left_cursor, "cub", "move #1 characters to the left (P)"},
  Capability{String::parm_right_cursor, "cuf", "move #1 characters to the right (P*)"},
  Capability{String::parm_rindex, "rin", "scroll back #1 lines (P)"},
  Capability{String::parm_up_cursor, "cuu", "up #1 lines (P*)"},
  Capability{String::pkey_key, "pfkey", "program function key #1 to type string #2"},
  Capability{String::pkey_local, "pfloc", "program function key #1 to execute string #2"},
  Capability{String::pkey_xmit, "pfx", "program function key #1 to transmit string #2"},
  Capability{String::print_screen, "mc0", "print contents of screen"},
  Capability{String::prtr_off, "mc4", "turn off printer"},
  Capability{String::repeat_char, "rep", "repeat char #1 #2 times (P*)"},
  Capability{String::reset_1string, "rs1", "reset string"},
  Capability{String::reset_2string, "rs2", "reset string"},
  Capability{String::reset_3string, "rs3", "reset string"},
  Capability{String::reset_file, "rf", "name of reset file"},
  Capability{String::restore_cursor, "rc", "restore cursor to position of last save_cursor"},
  Capability{String::row_address, "vpa", "vertical position #1 absolute (P)"},
  Capability{String::save_cursor, "sc", "save current cursor position (P)"},
  Capability{String::scroll_forward, "ind", "scroll text up (P)"},
  Capability{String::scroll_reverse, "ri", "scroll text down (P)"},
  Capability{String::set_attributes, "sgr", "define video attributes #1-#9 (PG9)"},
  Capability{String::set_tab, "hts", "set a tab in every row, current columns"},
  Capability{String::set_window, "wind", "current window is lines #1-#2 cols #3-#4"},
  Capability{String::tab, "ht", "tab to next 8-space hardware tab stop"},
  Capability{String::to_status_line, "tsl", "move to status line, column #1"},
  Capability{String::underline_char, "uc", "underline char and move past it"},
  Capability{String::up_half_line, "hu", "half a line up"},
  Capability{String::init_prog, "iprog", "path name of program for initialization"},
  Capability{String::key_a1, "ka1", "upper left of keypad"},
  Capability{String::key_a3, "ka3", "upper right of keypad"},
  Capability{String::key_b2, "kb2", "center of keypad"},
  Capability{String::key_c1, "kc1", "lower left of keypad"},
  Capability{String::key_c3, "kc3", "lower right of keypad"},
  Capability{String::prtr_non, "mc5p", "turn on printer for #1 bytes"},
  Capability{String::char_padding, "rmp", "like ip but when in insert mode"},
  Capability{String::acs_chars, "acsc", "graphics charset pairs, based on vt100"},
  Capability{String::plab_norm, "pln", "program label #1 to show string #2"},
  Capability{String::key_btab, "kcbt", "back-tab key"},
  Capability{String::enter_xon_mode, "smxon", "turn on xon/xoff handshaking"},
  Capability{String::exit_xon_mode, "rmxon", "turn off xon/xoff handshaking"},
  Capability{String::enter_am_mode, "smam", "turn on automatic margins"},
  Capability{String::exit_am_mode, "rmam", "turn off automatic margins"},
  Capability{String::xon_character, "xonc", "XON character"},
  Capability{String::xoff_character, "xoffc", "XOFF character"},
  Capability{String::ena_acs, "enacs", "enable alternate char set"},
  Capability{String::label_on, "smln", "turn on soft labels"},
  Capability{String::label_off, "rmln", "turn off soft labels"},
  Capability{String::key_beg, "kbeg", "begin key"},
  Capability{String::key_cancel, "kcan", "cancel key"},
  Capability{String::key_close, "kclo", "close key"},
  Capability{String::key_command, "kcmd", "command key"},
  Capability{String::key_copy, "kcpy", "copy key"},
  Capability{String::key_create, "kcrt", "create key"},
  Capability{String::key_end, "kend", "end key"},
  Capability{String::key_enter, "kent", "enter/send key"},
  Capability{String::key_exit, "kext", "exit key"},
  Capability{String::key_find, "kfnd", "find key"},
  Capability{String::key_help, "khlp", "help key"},
  Capability{String::key_mark, "kmrk", "mark key"},
  Capability{String::key_message, "kmsg", "message key"},
  Capability{String::key_move, "kmov", "move key"},
  Capability{String::key_next, "knxt", "next key"},
  Capability{String::key_open, "kopn", "open key"},
  Capability{String::key_options, "kopt", "options key"},
  Capability{String::key_previous, "kprv", "previous key"},
  Capability{String::key_print, "kprt", "print key"},
  Capability{String::key_redo, "krdo", "redo key"},
  Capability{String::key_reference, "kref", "reference key"},
  Capability{String::key_refresh, "krfr", "refresh key"},
  Capability{String::key_replace, "krpl", "replace key"},
  Capability{String::key_restart, "krst", "restart key"},
  Capability{String::key_resume, "kres", "resume key"},
  Capability{String::key_save, "ksav", "save key"},
  Capability{String::key_suspend, "kspd", "suspend key"},
  Capability{String::key_undo, "kund", "undo key"},
  Capability{String::key_sbeg, "kBEG", "shifted begin key"},
  Capability{String::key_scancel, "kCAN", "shifted cancel key"},
  Capability{String::key_scommand, "kCMD", "shifted command key"},
  Capability{String::key_scopy, "kCPY", "shifted copy key"},
  Capability{String::key_screate, "kCRT", "shifted create key"},
  Capability{String::key_sdc, "kDC", "shifted delete-character key"},
  Capability{String::key_sdl, "kDL", "shifted delete-line key"},
  Capability{String::key_select, "kslt", "select key"},
  Capability{String::key_send, "kEND", "shifted end key"},
  Capability{String::key_seol, "kEOL", "shifted clear-to-end-of-line key"},
  Capability{String::key_sexit, "kEXT", "shifted exit key"},
  Capability{String::key_sfind, "kFND", "shifted find key"},
  Capability{String::key_shelp, "kHLP", "shifted help key"},
  Capability{String::key_shome, "kHOM", "shifted home key"},
  Capability{String::key_sic, "kIC", "shifted insert-character key"},
  Capability{String::key_sleft, "kLFT", "shifted left-arrow key"},
  Capability{String::key_smessage, "kMSG", "shifted message key"},
  Capability{String::key_smove, "kMOV", "shifted move key"},
  Capability{String::key_snext, "kNXT", "shifted next key"},
  Capability{String::key_soptions, "kOPT", "shifted options key"},
  Capability{String::key_sprevious, "kPRV", "shifted previous key"},
  Capability{String::key_sprint, "kPRT", "shifted print key"},
  Capability{String::key_sredo, "kRDO", "shifted redo key"},
  Capability{String::key_sreplace, "kRPL", "shifted replace key"},
  Capability{String::key_sright, "kRIT", "shifted right-arrow key"},
  Capability{String::key_srsume, "kRES", "shifted resume key"},
  Capability{String::key_ssave, "kSAV", "shifted save key"},
  Capability{String::key_ssuspend, "kSPD", "shifted suspend key"},
  Capability{String::key_sundo, "kUND", "shifted undo key"},
  Capability{String::req_for_input, "rfi", "send next input char (for ptys)"},
  Capability{String::key_f11, "kf11", "F11 function key"},
  Capability{String::key_f12, "kf12", "F12 function key"},
  Capability{String::key_f13, "kf13", "F13 function key"},
  Capability{String::key_f14, "kf14", "F14 function key"},
  Capability{String::key_f15, "kf15", "F15 function key"},
  Capability{String::key_f16, "kf16", "F16 function key"},
  Capability{String::key_f17, "kf17", "F17 function key"},
  Capability{String::key_f18, "kf18", "F18 function key"},
  Capability{String::key_f19, "kf19", "F19 function key"},
  Capability{String::key_f20, "kf20", "F20 function key"},
  Capability{String::key_f21, "kf21", "F21 function key"},
  Capability{String::key_f22, "kf22", "F22 function key"},
  Capability{String::key_f23, "kf23", "F23 function key"},
  Capability{String::key_f24, "kf24", "F24 function key"},
  Capability{String::key_f25, "kf25", "F25 function key"},
  Capability{String::key_f26, "kf26", "F26 function key"},
  Capability{String::key_f27, "kf27", "F27 function key"},
  Capability{String::key_f28, "kf28", "F28 function key"},
  Capability{String::key_f29, "kf29", "F29 function key"},
  Capability{String::key_f30, "kf30", "F30 function key"},
  Capability{String::key_f31, "kf31", "F31 function key"},
  Capability{String::key_f32, "kf32", "F32 function key"},
  Capability{String::key_f33, "kf33", "F33 function key"},
  Capability{String::key_f34, "kf34", "F34 function key"},
  Capability{String::key_f35, "kf35", "F35 function key"},
  Capability{String::key_f36, "kf36", "F36 function key"},
  Capability{String::key_f37, "kf37", "F37 function key"},
  Capability{String::key_f38, "kf38", "F38 function key"},
  Capability{String::key_f39, "kf39", "F39 function key"},
  Capability{String::key_f40, "kf40", "F40 function key"},
  Capability{String::key_f41, "kf41", "F41 function key"},
  Capability{String::key_f42, "kf42", "F42 function key"},
  Capability{String::key_f43, "kf43", "F43 function key"},
  Capability{String::key_f44, "kf44", "F44 function key"},
  Capability{String::key_f45, "kf45", "F45 function key"},
  Capability{String::key_f46, "kf46", "F46 function key"},
  Capability{String::key_f47, "kf47", "F47 function key"},
  Capability{String::key_f48, "kf48", "F48 function key"},
  Capability{String::key_f49, "kf49", "F49 function key"},
  Capability{String::key_f50, "kf50", "F50 function key"},
  Capability{String::key_f51, "kf51", "F51 function key"},
  Capability{String::key_f52, "kf52", "F52 function key"},
  Capability{String::key_f53, "kf53", "F53 function key"},
  Capability{String::key_f54, "kf54", "F54 function key"},
  Capability{String::key_f55, "kf55", "F55 function key"},
  Capability{String::key_f56, "kf56", "F56 function key"},
  Capability{String::key_f57, "kf57", "F57 function key"},
  Capability{String::key_f58, "kf58", "F58 function key"},
  Capability{String::key_f59, "kf59", "F59 function key"},
  Capability{String::key_f60, "kf60", "F60 function key"},
  Capability{String::key_f61, "kf61", "F61 function key"},
  Capability{String::key_f62, "kf62", "F62 function key"},
  Capability{String::key_f63, "kf63", "F63 function key"},
  Capability{String::clr_bol, "el1", "Clear to beginning of line"},
  Capability{String::clear_margins, "mgc", "clear right and left soft margins"},
  Capability{String::set_left_margin, "smgl", "set left soft margin at current column (not in BSD termcap)"},
  Capability{String::set_right_margin, "smgr", "set right soft margin at current column"},
  Capability{String::label_format, "fln", "label format"},
  Capability{String::set_clock, "sclk", "set clock, #1 hrs #2 mins #3 secs"},
  Capability{String::display_clock, "dclk", "display clock"},
  Capability{String::remove_clock, "rmclk", "remove clock"},
  Capability{String::create_window, "cwin", "define a window #1 from #2,#3 to #4,#5"},
  Capability{String::goto_window, "wingo", "go to window #1"},
  Capability{String::hangup, "hup", "hang-up phone"},
  Capability{String::dial_phone, "dial", "dial number #1"},
  Capability{String::quick_dial, "qdial", "dial number #1 without checking"},
  Capability{String::tone, "tone", "select touch tone dialing"},
  Capability{String::pulse, "pulse", "select pulse dialing"},
  Capability{String::flash_hook, "hook", "flash switch hook"},
  Capability{String::fixed_pause, "pause", "pause for 2-3 seconds"},
  Capability{String::wait_tone, "wait", "wait for dial-tone"},
  Capability{String::user0, "u0", "User string #0"},
  Capability{String::user1, "u1", "User string #1"},
  Capability{String::user2, "u2", "User string #2"},
  Capability{String::user3, "u3", "User string #3"},
  Capability{String::user4, "u4", "User string #4"},
  Capability{String::user5, "u5", "User string #5"},
  Capability{String::user6, "u6", "User string #6"},
  Capability{String::user7, "u7", "User string #7"},
  Capability{String::user8, "u8", "User string #8"},
  Capability{String::user9, "u9", "User string #9"},
  Capability{String::orig_pair, "op", "Set default pair to its original value"},
  Capability{String::orig_colors, "oc", "Set all color pairs to the original ones"},
  Capability{String::initialize_color, "initc", "initialize color #1 to (#2,#3,#4)"},
  Capability{String::initialize_pair, "initp", "Initialize color pair #1 to fg=(#2,#3,#4), bg=(#5,#6,#7)"},
  Capability{String::set_color_pair, "scp", "Set current color pair to #1"},
  Capability{String::set_foreground, "setf", "Set foreground color #1"},
  Capability{String::set_background, "setb", "Set background color #1"},
  Capability{String::change_char_pitch, "cpi", "Change number of characters per inch to #1"},
  Capability{String::change_line_pitch, "lpi", "Change number of lines per inch to #1"},
  Capability{String::change_res_horz, "chr", "Change horizontal resolution to #1"},
  Capability{String::change_res_vert, "cvr", "Change vertical resolution to #1"},
  Capability{String::define_char, "defc", "Define a character #1, #2 dots wide, descender #3"},
  Capability{String::enter_doublewide_mode, "swidm", "Enter double-wide mode"},
  Capability{String::enter_draft_quality, "sdrfq", "Enter draft-quality mode"},
  Capability{String::enter_italics_mode, "sitm", "Enter italic mode"},
  Capability{String::enter_leftward_mode, "slm", "Start leftward carriage motion"},
  Capability{String::enter_micro_mode, "smicm", "Start micro-motion mode"},
  Capability{String::enter_near_letter_quality, "snlq", "Enter NLQ mode"},
  Capability{String::enter_normal_quality, "snrmq", "Enter normal-quality mode"},
  Capability{String::enter_shadow_mode, "sshm", "Enter shadow-print mode"},
  Capability{String::enter_subscript_mode, "ssubm", "Enter subscript mode"},
  Capability{String::enter_superscript_mode, "ssupm", "Enter superscript mode"},
  Capability{String::enter_upward_mode, "sum", "Start upward carriage motion"},
  Capability{String::exit_doublewide_mode, "rwidm", "End double-wide mode"},
  Capability{String::exit_italics_mode, "ritm", "End italic mode"},
  Capability{String::exit_leftward_mode, "rlm", "End left-motion mode"},
  Capability{String::exit_micro_mode, "rmicm", "End micro-motion mode"},
  Capability{String::exit_shadow_mode, "rshm", "End shadow-print mode"},
  Capability{String::exit_subscript_mode, "rsubm", "End subscript mode"},
  Capability{String::exit_superscript_mode, "rsupm", "End superscript mode"},
  Capability{String::exit_upward_mode, "rum", "End reverse character motion"},
  Capability{String::micro_column_address, "mhpa", "Like column_address in micro mode"},
  Capability{String::micro_down, "mcud1", "Like cursor_down in micro mode"},
  Capability{String::micro_left, "mcub1", "Like cursor_left in micro mode"},
  Capability{String::micro_right, "mcuf1", "Like cursor_right in micro mode"},
  Capability{String::micro_row_address, "mvpa", "Like row_address #1 in micro mode"},
  Capability{String::micro_up, "mcuu1", "Like cursor_up in micro mode"},
  Capability{String::order_of_pins, "porder", "Match software bits to print-head pins"},
  Capability{String::parm_down_micro, "mcud", "Like parm_down_cursor in micro mode"},
  Capability{String::parm_left_micro, "mcub", "Like parm_left_cursor in micro mode"},
  Capability{String::parm_right_micro, "mcuf", "Like parm_right_cursor in micro mode"},
  Capability{String::parm_up_micro, "mcuu", "Like parm_up_cursor in micro mode"},
  Capability{String::select_char_set, "scs", "Select character set, #1"},
  Capability{String::set_bottom_margin, "smgb", "Set bottom margin at current line"},
  Capability{String::set_bottom_margin_parm, "smgbp",
             "Set bottom margin at line #1 or (if smgtp is not given) #2 "
             "lines from bottom"},
  Capability{String::set_left_margin_parm, "smglp", "Set left (right) margin at column #1"},
  Capability{String::set_right_margin_parm, "smgrp", "Set right margin at column #1"},
  Capability{String::set_top_margin, "smgt", "Set top margin at current line"},
  Capability{String::set_top_margin_parm, "smgtp", "Set top (bottom) margin at row #1"},
  Capability{String::start_bit_image, "sbim", "Start printing bit image graphics"},
  Capability{String::start_char_set_def, "scsd", "Start character set definition #1, with #2 characters in the set"},
  Capability{String::stop_bit_image, "rbim", "Stop printing bit image graphics"},
  Capability{String::stop_char_set_def, "rcsd", "End definition of character set #1"},
  Capability{String::subscript_characters, "subcs", "List of subscriptable characters"},
  Capability{String::superscript_characters, "supcs", "List of superscriptable characters"},
  Capability{String::these_cause_cr, "docr", "Printing any of these characters causes CR"},
  Capability{String::zero_motion, "zerom", "No motion for subsequent character"},
  Capability{String::char_set_names, "csnm", "Produce #1'th item from list of character set names"},
  Capability{String::key_mouse, "kmous", "Mouse event has occurred"},
  Capability{String::mouse_info, "minfo", "Mouse status information"},
  Capability{String::req_mouse_pos, "reqmp", "Request mouse position"},
  Capability{String::get_mouse, "getm", "Curses should get button events, parameter #1 not documented."},
  Capability{String::set_a_foreground, "setaf", "Set foreground color to #1, using ANSI escape"},
  Capability{String::set_a_background, "setab", "Set background color to #1, using ANSI escape"},
  Capability{String::pkey_plab, "pfxl", "Program function key #1 to type string #2 and show string #3"},
  Capability{String::device_type, "devt", "Indicate language, codeset support"},
  Capability{String::code_set_init, "csin", "Init sequence for multiple codesets"},
  Capability{String::set0_des_seq, "s0ds", "Shift to codeset 0 (EUC set 0, ASCII)"},
  Capability{String::set1_des_seq, "s1ds", "Shift to codeset 1"},
  Capability{String::set2_des_seq, "s2ds", "Shift to codeset 2"},
  Capability{String::set3_des_seq, "s3ds", "Shift to codeset 3"},
  Capability{String::set_lr_margin, "smglr",
             "Set both left and right margins to #1, #2.  (ML is not in "
             "BSD termcap)."},
  Capability{String::set_tb_margin, "smgtb", "Sets both top and bottom margins to #1, #2"},
  Capability{String::bit_image_repeat, "birep", "Repeat bit image cell #1 #2 times"},
  Capability{String::bit_image_newline, "binel", "Move to next row of the bit image"},
  Capability{String::bit_image_carriage_return, "bicr", "Move to beginning of same row"},
  Capability{String::color_names, "colornm", "Give name for color #1"},
  Capability{String::define_bit_image_region, "defbi", "Define rectangular bit image region"},
  Capability{String::end_bit_image_region, "endbi", "End a bit-image region"},
  Capability{String::set_color_band, "setcolor", "Change to ribbon color #1"},
  Capability{String::set_page_length, "slines", "Set page length to #1 lines"},
  Capability{String::display_pc_char, "dispc", "Display PC character #1"},
  Capability{String::enter_pc_charset_mode, "smpch", "Enter PC character display mode"},
  Capability{String::exit_pc_charset_mode, "rmpch", "Exit PC character display mode"},
  Capability{String::enter_scancode_mode, "smsc", "Enter PC scancode mode"},
  Capability{String::exit_scancode_mode, "rmsc", "Exit PC scancode mode"},
  Capability{String::pc_term_options, "pctrm", "PC terminal options"},
  Capability{String::scancode_escape, "scesc", "Escape for scancode emulation"},
  Capability{String::alt_scancode_esc, "scesa", "Alternate escape for scancode emulation"},
  Capability{String::enter_horizontal_hl_mode, "ehhlm", "Enter horizontal highlight mode"},
  Capability{String::enter_left_hl_mode, "elhlm", "Enter left highlight mode"},
  Capability{String::enter_low_hl_mode, "elohlm", "Enter low highlight mode"},
  Capability{String::enter_right_hl_mode, "erhlm", "Enter right highlight mode"},
  Capability{String::enter_top_hl_mode, "ethlm", "Enter top highlight mode"},
  Capability{String::enter_vertical_hl_mode, "evhlm", "Enter vertical highlight mode"},
  Capability{String::set_a_attributes, "sgr1", "Define second set of video attributes #1-#6"},
  Capability{String::set_pglen_inch, "slength",
             "Set page length to #1 hundredth of an inch (some "
             "implementations use sL for termcap)."},
  // Others
  Capability{String::set_underline_color, "setal", "set (under)line color"},
  Capability{String::lock_memory_above_cursor, "meml", "locks memory above the cursor (ala HP terminals)"},
  Capability{String::unlock_memory_above_cursor, "memu", "unlocks memory above the cursor (ala HP terminals)"},
  Capability{String::enable_real_bold, "gsbom", " enable real bold (not intensity bright) mode"},
  Capability{String::disable_real_bold, "grbom", "disable real bold (not intensity bright) mode"},
  Capability{String::mouse_response, "xm", "describes the mouse response"},
  Capability{String::enable_focus_events, "fe", "enables focus events"},
  Capability{String::disable_focus_events, "fd", "disables focus events"},
  Capability{String::turn_on_printer, "mc5", "turn on printer"},
  Capability{String::set_cursor_color, "Cs", "set cursor color"},
  Capability{String::reset_cursor_color, "Cr", "reset cursor color"},
  Capability{String::modify_selection_clipboard, "Ms", "modifies the selection/clipboard"},
};

Terminfo::Boolean Terminfo::Capabilities::getBoolean(const std::string& str)
{
  const Terminfo::Capability* found = std::find(m_booleans.begin(), m_booleans.end(), str);
  if(found != m_booleans.end()) return static_cast<Terminfo::Boolean>(found->value());
  throw std::out_of_range(str);
}

Terminfo::Integer Terminfo::Capabilities::getInteger(const std::string& str)
{
  const Terminfo::Capability* found = std::find(m_integers.begin(), m_integers.end(), str);
  if(found != m_integers.end()) return static_cast<Terminfo::Integer>(found->value());
  throw std::out_of_range(str);
}

Terminfo::String Terminfo::Capabilities::getString(const std::string& str)
{
  const Terminfo::Capability* found = std::find(m_strings.begin(), m_strings.end(), str);
  if(found != m_strings.end()) return static_cast<Terminfo::String>(found->value());
  throw std::out_of_range(str);
}
