OLED_ENABLE = yes   # Enables the use of OLED displays
OLED_DRIVER = SSD1306
ENCODER_ENABLE = yes       # Enables the use of one or more encoders
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
MOUSEKEY_ENABLE = no
COMBO_ENABLE = no
COMMAND_ENABLE = no
KEY_LOCK_ENABLE = no
EXTRAFLAGS += -flto

SRC += snow.c
SRC += brush.c
SRC += etch.c