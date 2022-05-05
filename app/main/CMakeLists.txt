# # add oled srcdir
# set(APP_DRIVERS_SRCS_OLED "drivers/oleds/src/oled.c")
# set(APP_DRIVERS_SRCDIRS_OLED "drivers/oleds/src")
# set(APP_DRIVERS_INCLUDEDIRS_OLED "drivers/oleds/include")

# # add APP_DRIVERS_SRCDIRS
# set(APP_DRIVERS_SRCS ${APP_DRIVERS_SRCS_OLED})
# set(APP_DRIVERS_SRCDIRS ${APP_DRIVERS_SRCDIRS_OLED})
# set(APP_DRIVERS_INCLUDEDIRS ${APP_DRIVERS_INCLUDEDIRS_OLED})


# # add component define
# set(COMPONENT_ADD_INCLUDEDIRS ${APP_DRIVERS_INCLUDEDIRS})
# set(COMPONENT_SRCDIRS ${APP_DRIVERS_SRCDIRS})
# set(COMPONENT_SRCS ${APP_DRIVERS_SRCS}
#                     "app_main.c")

set(COMPONENT_SRCS "app_main.c")

register_component()
