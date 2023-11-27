# ccache
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
elseif()
    message(FATAL_ERROR "Couldnt find ccache")
endif(CCACHE_FOUND)
