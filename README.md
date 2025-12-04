# ICMP-HUE (ICMP Hidden User Exchange)

## Covert Data Transmission over the Internet Control Message Protocol

## 1. Project Overview

The **ICMP-HUE** (ICMP Hidden User Exchange) is basically an **ICMP Tunneling**, specifically using the **Echo Request** (`ping`) to transmit arbitrary data.

While ICMP is designed for control and error messages, ICMP-HUE encapsulates a data payload within the normally empty data section of an ICMP packet. This allows for communication that can bypass network filters configured to allow only standard ICMP traffic but block conventional TCP/UDP ports. 

## 2. System Components

The system consists of two minimal C applications utilizing raw sockets:

| Component | Role | Description |
| :--- | :--- | :--- |
| **`icmp_server`** | **Receiver** | Listens on a **raw socket** (`SOCK_RAW`) for incoming ICMP packets, filters for Type 8 (Echo Request), and extracts the hidden user message from the packet payload. |
| **`icmp_client`** | **Transmitter** | Constructs a complete ICMP `Echo Request` packet, inserts the user's message as the data payload, calculates the necessary ICMP **checksum**, and sends the raw packet to the destination IP. |

## 4. Building the Application

Use the provided `Makefile` to compile both source files.

```bash
make