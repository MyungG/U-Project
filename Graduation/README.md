# Graduation_Project

Contents of graduation works developed over the course of one year, The purpose of this project is that detects fire and sprays water at the exact point of fire

## Project Name
Fire Early Suppression Sprinklers

## Outline
- **Using a thermal imaging camera** and **image processing** technology to identify the fire point and determine whether there is a fire
- **Motion control** is used to move the nozzle to the fire point with an **X-Y plotter** and perform a water jet motion for complete fire suppression.
- Water is sprayed at the point of fire by using a **pump motor and a solenoid valve**.

## This Readme File contains:
- [Development Background](DevelopmentBackground)
- [System Diagram](SystemDiagram)  
- [Final Result](FinalResult)  
- [My Role](MyRole)  

## Development Background
1. Sprinkler malfunction, no effect in case of fire
2. Extensive water spraying of conventional sprinklers has a high probability of causing plant equipment failure

## System Diagram
![image](https://user-images.githubusercontent.com/64455972/126889187-b2796456-d946-4f7d-b166-c861dcdc0d1c.png)

## Final Result
![image](https://user-images.githubusercontent.com/64455972/126889219-fe9f2f52-c7ca-4e48-99d4-9c34d52e5da9.png)

## My Role

When the flame sensor detects a fire, it sends it to the PC, and when it receives a water spray command from the PC, it sprays water through the pump motor and solenoid valve control.

1. Circuit design - MCU peripheral circuit, driver circuit to control pump motor and solenoid valve, regulator circuit
2. Firmware creation

![image](https://user-images.githubusercontent.com/64455972/126889228-b29e9c23-0b9e-43f8-aa31-59442f764f31.png)
 
