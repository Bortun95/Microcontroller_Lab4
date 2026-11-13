# Lab 4: Cooperative Scheduler

**School:** Ho Chi Minh City University of Technology (HCMUT)  
**Name:** Huynh Tri Duc  
**Student ID:** 2452269  
**Group:** CC03  

---

### Project Overview  
Source code and Proteus simulation for Lab 4, implementing a **Time-Triggered Cooperative Scheduler** on STM32F103C6. The application overcomes the timing unpredictability and jitter of traditional Super Loop architectures by separating timebase counting (executed inside a 10ms hardware timer interrupt `TIM2`) from task execution (dispatched in the main background loop `while (1)`). 

To satisfy strict real-time embedded constraints, the scheduler implements a **Delta Queue (Differential Delay Queue)** data structure, reducing the interrupt update complexity to strictly $\mathcal{O}(1)$ instead of $\mathcal{O}(n)$ linear scanning. The system concurrently manages 5 periodic tasks driving 5 colored LEDs (0.5s, 1.0s, 1.5s, 2.0s, 2.5s), multiple one-shot tasks, dynamic task deletion by unique `TaskID`, and a real-time timestamp logging stream via `USART1` at 115200 baud with 10ms resolution (`get_time()`).

---

### Tools & Environment  
- **Microcontroller:** STM32F103C6 (ARM Cortex-M3, 8 MHz HSI Clock)  
- **Development Environment:** STM32CubeIDE  
- **Simulation:** Proteus 8 Professional  
- **Communication / Terminal:** Proteus VSM Virtual Terminal (`115200` bps, `8-N-1`)  

---

### Pin Mapping  

| Component | MCU Pin | Type | Function |
| :--- | :--- | :--- | :--- |
| **LED_BLUE (D1)** | `PB0` | GPIO Output (Push-Pull) | Blue LED Indicator (0.5s periodic toggle) |
| **LED_GREEN (D2)** | `PB1` | GPIO Output (Push-Pull) | Green LED Indicator (1.0s periodic toggle) |
| **LED_PURPLE (D3)** | `PB2` | GPIO Output (Push-Pull) | Purple LED Indicator (1.5s periodic toggle) |
| **LED_RED (D4)** | `PB3` | GPIO Output (Push-Pull) | Red LED Indicator (2.0s periodic toggle) |
| **LED_YELLOW (D5)** | `PB4` | GPIO Output (Push-Pull) | Yellow LED Indicator (2.5s periodic toggle) |
| **USART1_TX** | `PA9` | Alternate Function PP | Serial TX to Virtual Terminal `RXD` (115200 baud) |
| **USART1_RX** | `PA10` | Input Floating | Serial RX from Virtual Terminal `TXD` |

---

### How to Run the Simulation  
1. Open the project in **STM32CubeIDE** and build the project (`Ctrl + B`) to generate the binary `.hex` file in the `Debug/` folder. *(Ensure `Convert to Intel Hex file` is enabled in Project Settings)*.  
2. Open the Proteus simulation file (`.pdsprj`) in **Proteus 8 Professional**.  
3. Double-click the `STM32F103C6` microcontroller:  
   - Set **Program File** to the compiled `.hex` file.  
   - Ensure **Crystal Frequency** is set to `8MHz`.  
4. Configure the **Virtual Terminal**:  
   - Baud Rate: `115200`  
   - Data Bits: `8`, Parity: `NONE`, Stop Bits: `1`  
   - Wire connections: `PA9` (TX) $\rightarrow$ `RXD`, `PA10` (RX) $\rightarrow$ `TXD`.  
5. Click **Play (Run Simulation)**:  
   - If the terminal window is hidden, open it via top menu: **Debug > Virtual Terminal**.  
   - Observe the 5 LEDs toggling at respective intervals (0.5s, 1.0s, 1.5s, 2.0s, 2.5s).  
   - Verify continuous 10ms timestamps (`t=...`), followed by one-shot trigger logs (`[OS1] t=3000`, `[OS2] t=4000`, `[OS3] t=5000`) and individual LED toggle timestamps.
