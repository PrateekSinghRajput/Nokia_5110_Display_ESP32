# Nokia 5110 LCD Display with ESP32 🚀📟

Welcome to the **Nokia 5110 Display ESP32** repository! This project demonstrates how to interface the classic Nokia 5110 LCD (PCD8544) with the ESP32 microcontroller to display text, graphics, and shapes with ease. Perfect for embedded projects requiring a small, monochrome graphical display.

---

## Features ✨

- Easy-to-use library for Nokia 5110 LCD with ESP32  
- Supports displaying text in multiple font sizes  
- Draw geometric shapes: lines, rectangles, circles, filled shapes  
- Custom graphics rendering (e.g., spirograph demo)  
- SPI interface with configurable pins and frequency  
- Simple initialization and control commands  

---

## Hardware Setup 🔧

Connect your Nokia 5110 LCD to the ESP32 as follows:

| Nokia 5110 Pin | ESP32 Pin        | Description           |
|----------------|------------------|-----------------------|
| RST            | GPIO 15          | Reset                 |
| CE (CS)        | GPIO 2           | Chip Select           |
| DC             | GPIO 19          | Data/Command select   |
| DIN (MOSI)     | GPIO 23          | SPI MOSI              |
| CLK (SCK)      | GPIO 18          | SPI Clock             |
| VCC            | 3.3V             | Power Supply          |
| BL             | 3.3V via 470Ω    | Backlight LED         |
| GND            | GND              | Ground                |

---


---

## Demo Highlights 🎨

- Display multiple lines of text with different font sizes  
- Draw rectangles, lines, circles, and filled shapes  
- Render custom spirograph patterns for graphic demos  

---

## Contributing 🤝

Contributions, issues, and feature requests are welcome! Feel free to check issues page and submit pull requests.

---

❤️ 

