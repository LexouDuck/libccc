#! This file holds some convenience variables to output text to the commandline



#! The shell command to print a makefile error message (one parameter: the message)
print_error   = printf $(IO_RED)"Error"$(IO_RESET)": "$(1)"\n" && exit 1
#! The shell command to print a makefile warning message (one parameter: the message)
print_warning = printf $(IO_YELLOW)"Warning"$(IO_RESET)": "$(1)"\n"
#! The shell command to print a makefile success message (one parameter: the message)
print_success = printf $(IO_GREEN)"Success"$(IO_RESET)": "$(1)"\n"
#! The shell command to print a makefile info message (one parameter: the message)
print_message = printf $(IO_CYAN)$(1)$(IO_RESET)"\n"
