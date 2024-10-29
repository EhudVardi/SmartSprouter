import os
import subprocess
import tkinter as tk
from tkinter import filedialog, scrolledtext
import json

# Configuration file to store last paths
CONFIG_FILE = "addr2line_config.json"

# Load saved configuration
def load_config():
    if os.path.exists(CONFIG_FILE):
        with open(CONFIG_FILE, "r") as f:
            return json.load(f)
    return {"addr2line_path": "", "elf_path": ""}

# Save configuration
def save_config(addr2line_path, elf_path):
    with open(CONFIG_FILE, "w") as f:
        json.dump({"addr2line_path": addr2line_path, "elf_path": elf_path}, f)

# Run addr2line and process backtrace
def run_addr2line():
    addr2line_path = addr2line_entry.get()
    elf_path = elf_entry.get()
    backtrace = backtrace_entry.get("1.0", tk.END).strip()

    # Extract addresses from backtrace
    addresses = [addr.split(':')[0] for addr in backtrace.split() if addr.startswith("0x")]

    if not os.path.isfile(addr2line_path) or not os.path.isfile(elf_path):
        output_text.insert(tk.END, "Invalid addr2line or ELF file path.\n")
        return

    output_text.delete("1.0", tk.END)  # Clear previous output

    try:
        for address in addresses:
            result = subprocess.run(
                [addr2line_path, "-e", elf_path, address],
                capture_output=True,
                text=True
            )
            output_text.insert(tk.END, f"{result.stdout.strip()}\n")
    except Exception as e:
        output_text.insert(tk.END, f"Error: {str(e)}\n")

    # Save the paths for future use
    save_config(addr2line_path, elf_path)

# Browse for addr2line executable
def browse_addr2line():
    filename = filedialog.askopenfilename(title="Select addr2line executable")
    addr2line_entry.delete(0, tk.END)
    addr2line_entry.insert(tk.END, filename)

# Browse for ELF file
def browse_elf():
    filename = filedialog.askopenfilename(title="Select ELF file")
    elf_entry.delete(0, tk.END)
    elf_entry.insert(tk.END, filename)

# GUI setup
root = tk.Tk()
root.title("Addr2line Backtrace Translator")
root.geometry("800x400")
root.minsize(800, 400)

config = load_config()

# Addr2line Path
tk.Label(root, text="Addr2line Path:").grid(row=0, column=0, sticky="w")
addr2line_entry = tk.Entry(root, width=80)
addr2line_entry.grid(row=0, column=1, padx=5, pady=5, sticky="ew")
addr2line_entry.insert(tk.END, config.get("addr2line_path", ""))
addr2line_button = tk.Button(root, text="Browse", command=browse_addr2line)
addr2line_button.grid(row=0, column=2, padx=5, pady=5)

# ELF File Path
tk.Label(root, text="ELF File Path:").grid(row=1, column=0, sticky="w")
elf_entry = tk.Entry(root, width=80)
elf_entry.grid(row=1, column=1, padx=5, pady=5, sticky="ew")
elf_entry.insert(tk.END, config.get("elf_path", ""))
elf_button = tk.Button(root, text="Browse", command=browse_elf)
elf_button.grid(row=1, column=2, padx=5, pady=5)

# Backtrace Input Field
tk.Label(root, text="Backtrace:").grid(row=2, column=0, sticky="w")
backtrace_entry = tk.Text(root, height=3, wrap="word")
backtrace_entry.grid(row=2, column=1, columnspan=2, padx=5, pady=5, sticky="nsew")

# Output Field
tk.Label(root, text="Output:").grid(row=3, column=0, sticky="nw")
output_text = scrolledtext.ScrolledText(root, wrap="word", height=20)
output_text.grid(row=3, column=1, columnspan=2, padx=5, pady=5, sticky="nsew")

# Run Button
run_button = tk.Button(root, text="Translate Backtrace", command=run_addr2line)
run_button.grid(row=4, column=1, columnspan=2, pady=10)

# Configure grid stretching
root.grid_rowconfigure(3, weight=1)
root.grid_columnconfigure(1, weight=1)

# Start GUI
root.mainloop()
