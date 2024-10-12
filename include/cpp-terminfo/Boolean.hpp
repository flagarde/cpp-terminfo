/*
 * cpp-terminfo
 * C++ standalone library for terminal terminfo capabilities.
 *
 * SPDX-FileCopyrightText: 2023-2024 cpp-terminfo
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once
#include <cstdint>

namespace Terminfo
{

enum class Boolean : std::uint8_t
{
  auto_left_margin = 1,
  auto_right_margin,
  no_esc_ctlc,
  ceol_standout_glitch,
  eat_newline_glitch,
  erase_overstrike,
  generic_type,
  hard_copy,
  has_meta_key,
  has_status_line,
  insert_null_glitch,
  memory_above,
  memory_below,
  move_insert_mode,
  move_standout_mode,
  over_strike,
  status_line_esc_ok,
  dest_tabs_magic_smso,
  tilde_glitch,
  transparent_underline,
  xon_xoff,
  needs_xon_xoff,
  prtr_silent,
  hard_cursor,
  non_rev_rmcup,
  no_pad_char,
  non_dest_scroll_region,
  can_change,
  back_color_erase,
  hue_lightness_saturation,
  col_addr_glitch,
  cr_cancels_micro_mode,
  has_print_wheel,
  row_addr_glitch,
  semi_auto_right_margin,
  cpi_changes_res,
  lpi_changes_res,
};

}