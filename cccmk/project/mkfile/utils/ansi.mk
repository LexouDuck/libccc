#! This file holds useful variables to color/style output terminal text (ANSI escape sequences)



#! This function simply puts ANSI escape-sequence delimiters around the given string
#	@param 1	should be a valid ANSI number string
ANSI="\033[$(1)m"



#! The ANSI escape sequences for simple colored terminal output
#{
IO_RESET        :=$(call ANSI,0)#!< ANSI escape sequence to reset terminal output to its default style
IO_BLACK        :=$(call ANSI,0;30)#!< ANSI escape sequence for colored terminal output black
IO_RED          :=$(call ANSI,0;31)#!< ANSI escape sequence for colored terminal output red
IO_GREEN        :=$(call ANSI,0;32)#!< ANSI escape sequence for colored terminal output green
IO_YELLOW       :=$(call ANSI,0;33)#!< ANSI escape sequence for colored terminal output yellow
IO_BLUE         :=$(call ANSI,0;34)#!< ANSI escape sequence for colored terminal output blue
IO_MAGENTA      :=$(call ANSI,0;35)#!< ANSI escape sequence for colored terminal output magenta
IO_CYAN         :=$(call ANSI,0;36)#!< ANSI escape sequence for colored terminal output cyan
IO_GRAY         :=$(call ANSI,0;37)#!< ANSI escape sequence for colored terminal output light gray
IO_DARK         :=$(call ANSI,0;90)#!< ANSI escape sequence for colored terminal output dark gray
IO_LIGHTRED     :=$(call ANSI,0;91)#!< ANSI escape sequence for colored terminal output light red
IO_LIGHTGREEN   :=$(call ANSI,0;92)#!< ANSI escape sequence for colored terminal output light green
IO_LIGHTYELLOW  :=$(call ANSI,0;93)#!< ANSI escape sequence for colored terminal output light yellow
IO_LIGHTBLUE    :=$(call ANSI,0;94)#!< ANSI escape sequence for colored terminal output light blue
IO_LIGHTMAGENTA :=$(call ANSI,0;95)#!< ANSI escape sequence for colored terminal output light magenta
IO_LIGHTCYAN    :=$(call ANSI,0;96)#!< ANSI escape sequence for colored terminal output light cyan
IO_WHITE        :=$(call ANSI,0;97)#!< ANSI escape sequence for colored terminal output white
#}



ANSI_RESET                  :=$(call ANSI,0)#!< ANSI escape sequence to reset the terminal text output to its default color

ANSI_TEXT_BOLD              :=$(call ANSI,1)#!< Display terminal output text in bold
ANSI_TEXT_DIM               :=$(call ANSI,2)#!< Display terminal output text with dimmer, darker colors
ANSI_TEXT_3                 :=$(call ANSI,3)#!< ???
ANSI_TEXT_UNDERLINE         :=$(call ANSI,4)#!< Display terminal output text with an underline
ANSI_TEXT_BLINK             :=$(call ANSI,5)#!< Display terminal output text which blinks every second (only in tty and xterm)
ANSI_TEXT_6                 :=$(call ANSI,6)#!< ???
ANSI_TEXT_INVERTED          :=$(call ANSI,7)#!< Display terminal output text with the background/foreground colors reversed
ANSI_TEXT_HIDDEN            :=$(call ANSI,8)#!< Write, but do not display, the terminal output text (useful for passwords)
ANSI_TEXT_9                 :=$(call ANSI,9)#!< ???

ANSI_TEXT_RESET_BOLD        :=$(call ANSI,21)#!< Undoes the effects of #ANSI_TEXT_BOLD
ANSI_TEXT_RESET_DIM         :=$(call ANSI,22)#!< Undoes the effects of #ANSI_TEXT_DIM
ANSI_TEXT_RESET_3           :=$(call ANSI,23)#!< Undoes the effects of #ANSI_TEXT_3
ANSI_TEXT_RESET_UNDERLINE   :=$(call ANSI,24)#!< Undoes the effects of #ANSI_TEXT_UNDERLINE
ANSI_TEXT_RESET_BLINK       :=$(call ANSI,25)#!< Undoes the effects of #ANSI_TEXT_BLINK
ANSI_TEXT_RESET_6           :=$(call ANSI,26)#!< Undoes the effects of #ANSI_TEXT_6
ANSI_TEXT_RESET_INVERTED    :=$(call ANSI,27)#!< Undoes the effects of #ANSI_TEXT_INVERTED
ANSI_TEXT_RESET_HIDDEN      :=$(call ANSI,28)#!< Undoes the effects of #ANSI_TEXT_HIDDEN
ANSI_TEXT_RESET_9           :=$(call ANSI,29)#!< Undoes the effects of #ANSI_TEXT_9



ANSI_COLOR_FG_BLACK         :=$(call ANSI,30)#!< ANSI escape sequence to color the terminal text output black
ANSI_COLOR_FG_RED           :=$(call ANSI,31)#!< ANSI escape sequence to color the terminal text output red
ANSI_COLOR_FG_GREEN         :=$(call ANSI,32)#!< ANSI escape sequence to color the terminal text output green
ANSI_COLOR_FG_YELLOW        :=$(call ANSI,33)#!< ANSI escape sequence to color the terminal text output yellow
ANSI_COLOR_FG_BLUE          :=$(call ANSI,34)#!< ANSI escape sequence to color the terminal text output blue
ANSI_COLOR_FG_MAGENTA       :=$(call ANSI,35)#!< ANSI escape sequence to color the terminal text output magenta
ANSI_COLOR_FG_CYAN          :=$(call ANSI,36)#!< ANSI escape sequence to color the terminal text output cyan
ANSI_COLOR_FG_GRAY_LIGHT    :=$(call ANSI,37)#!< ANSI escape sequence to color the terminal text output light gray
ANSI_COLOR_FG_GRAY_DARK     :=$(call ANSI,90)#!< ANSI escape sequence to color the terminal text output dark gray
ANSI_COLOR_FG_RED_LIGHT     :=$(call ANSI,91)#!< ANSI escape sequence to color the terminal text output light red
ANSI_COLOR_FG_GREEN_LIGHT   :=$(call ANSI,92)#!< ANSI escape sequence to color the terminal text output light green
ANSI_COLOR_FG_YELLOW_LIGHT  :=$(call ANSI,93)#!< ANSI escape sequence to color the terminal text output light yellow
ANSI_COLOR_FG_BLUE_LIGHT    :=$(call ANSI,94)#!< ANSI escape sequence to color the terminal text output light blue
ANSI_COLOR_FG_MAGENTA_LIGHT :=$(call ANSI,95)#!< ANSI escape sequence to color the terminal text output light magenta
ANSI_COLOR_FG_CYAN_LIGHT    :=$(call ANSI,96)#!< ANSI escape sequence to color the terminal text output light cyan
ANSI_COLOR_FG_WHITE         :=$(call ANSI,97)#!< ANSI escape sequence to color the terminal text output white

#! ANSI Color code (255-map, not supported on certain old terminals)
#	@param 1	should be a string, containing number between 0 and 255
ANSI_COLOR_FG=$(call ANSI,38;5;$(1))

#! ANSI escape sequence to color the terminal text output with the default color for this terminal
ANSI_COLOR_FG_DEFAULT       :=$(call ANSI,39)



ANSI_COLOR_BG_BLACK         :=$(call ANSI,40)#!< ANSI escape sequence to color the terminal text background/highlight black
ANSI_COLOR_BG_RED           :=$(call ANSI,41)#!< ANSI escape sequence to color the terminal text background/highlight red
ANSI_COLOR_BG_GREEN         :=$(call ANSI,42)#!< ANSI escape sequence to color the terminal text background/highlight green
ANSI_COLOR_BG_YELLOW        :=$(call ANSI,43)#!< ANSI escape sequence to color the terminal text background/highlight yellow
ANSI_COLOR_BG_BLUE          :=$(call ANSI,44)#!< ANSI escape sequence to color the terminal text background/highlight blue
ANSI_COLOR_BG_MAGENTA       :=$(call ANSI,45)#!< ANSI escape sequence to color the terminal text background/highlight magenta
ANSI_COLOR_BG_CYAN          :=$(call ANSI,46)#!< ANSI escape sequence to color the terminal text background/highlight cyan
ANSI_COLOR_BG_GRAY_LIGHT    :=$(call ANSI,47)#!< ANSI escape sequence to color the terminal text background/highlight light gray
ANSI_COLOR_BG_GRAY_DARK     :=$(call ANSI,100)#!< ANSI escape sequence to color the terminal text background/highlight dark gray
ANSI_COLOR_BG_RED_LIGHT     :=$(call ANSI,101)#!< ANSI escape sequence to color the terminal text background/highlight light red
ANSI_COLOR_BG_GREEN_LIGHT   :=$(call ANSI,102)#!< ANSI escape sequence to color the terminal text background/highlight light green
ANSI_COLOR_BG_YELLOW_LIGHT  :=$(call ANSI,103)#!< ANSI escape sequence to color the terminal text background/highlight light yellow
ANSI_COLOR_BG_BLUE_LIGHT    :=$(call ANSI,104)#!< ANSI escape sequence to color the terminal text background/highlight light blue
ANSI_COLOR_BG_MAGENTA_LIGHT :=$(call ANSI,105)#!< ANSI escape sequence to color the terminal text background/highlight light magenta
ANSI_COLOR_BG_CYAN_LIGHT    :=$(call ANSI,106)#!< ANSI escape sequence to color the terminal text background/highlight light cyan
ANSI_COLOR_BG_WHITE         :=$(call ANSI,107)#!< ANSI escape sequence to color the terminal text background/highlight white

#! ANSI Color code (255-map, not supported on certain old terminals)
#	@param 1	should be a string, containing number between 0 and 255
ANSI_COLOR_BG=$(call ANSI,48;5;$(1))

#! ANSI escape sequence to color the terminal text background with the default color for this terminal
ANSI_COLOR_BG_DEFAULT       :=$(call ANSI,49)
