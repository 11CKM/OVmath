SET(SOURCES screens/ui_WeclomeScreen.c
    screens/ui_SizeScreen.c
    screens/ui_TScreen.c
    screens/ui_DateScreen.c
    screens/ui_bybyScreen.c
    screens/ui_Hand.c
    screens/ui_Screen7.c
    screens/ui_TICK.c
    screens/ui_Screen8.c
    screens/ui_Screen1.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    fonts/ui_font_ALIBABAB6.c
    fonts/ui_font_huanzi30.c
    fonts/ui_font_ionc32.c
    fonts/ui_font_part.c
    fonts/ui_font_tianqhuanzi16.c
    fonts/ui_font_ALliBABA16.c)

add_library(ui ${SOURCES})
