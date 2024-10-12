/*
 * cpp-terminfo
 * C++ library for terminal terminfo capacities.
 *
 * SPDX-FileCopyrightText: 2019-2024 cpp-terminal
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once
#include <cstdint>

namespace Terminfo {

enum class Integer : std::uint8_t {
  columns,
  init_tabs,
  lines,
  lines_of_memory,
  magic_cookie_glitch,
  padding_baud_rate,
  virtual_terminal,
  width_status_line,
  num_labels,
  label_height,
  label_width,
  max_attributes,
  maximum_windows,
  max_colors,
  max_pairs,
  no_color_video,
  buffer_capacity,
  dot_vert_spacing,
  dot_horz_spacing,
  max_micro_address,
  max_micro_jump,
  micro_col_size,
  micro_line_size,
  number_of_pins,
  output_res_char,
  output_res_line,
  output_res_horz_inch,
  output_res_vert_inch,
  print_rate,
  wide_char_size,
  buttons,
  bit_image_entwining,
  bit_image_type,
};

}