# pip install Pillow

import sys
import os
from PIL import Image

def generate_bitmap_data(image_path, target_width=16, target_height=16):
    # Load the image
    try:
        image = Image.open(image_path)
    except FileNotFoundError:
        print(f"Error: Image file '{image_path}' not found.")
        return

    # Resize the image to the target size using LANCZOS (formerly ANTIALIAS)
    image = image.resize((target_width, target_height), Image.Resampling.LANCZOS)

    # Convert the image to black and white (1-bit pixels)
    image = image.convert("1")  # "1" means 1-bit pixels, black and white

    # Generate bitmap data
    bitmap_data = []
    for y in range(target_height):
        byte = 0
        for x in range(target_width):
            if image.getpixel((x, y)) == 0:  # Black pixel
                byte |= (1 << (7 - (x % 8)))  # Set the corresponding bit
            if (x % 8 == 7) or (x == target_width - 1):  # End of byte
                bitmap_data.append(byte)
                byte = 0

    return bitmap_data

def save_bitmap_data(bitmap_data, target_width, target_height, output_file):
    # Extract the image name for header guard
    image_name = os.path.splitext(os.path.basename(output_file))[0].upper()
    header_guard = f"{image_name}_H"

    # Print the bitmap data in C array format
    with open(output_file, 'w') as f:
        # Write the header guard
        f.write(f"#ifndef {header_guard}\n")
        f.write(f"#define {header_guard}\n\n")
        
        # Write the bitmap data
        f.write(f"const uint8_t {image_name.lower()}_bitmap[] = {{\n")
        for i in range(0, len(bitmap_data), 16):  # Print 16 bytes per line
            f.write("  ")
            f.write(", ".join(f"0b{bitmap_data[j]:08b}" for j in range(i, min(i + 16, len(bitmap_data)))))
            f.write(",\n")
        f.write("};\n\n")

        # Write the dimensions
        f.write(f"const int {image_name.lower()}_width = {target_width};\n")
        f.write(f"const int {image_name.lower()}_height = {target_height};\n\n")

        # End the header guard
        f.write(f"#endif // {header_guard}\n")

    print(f"Bitmap data saved to '{output_file}'.")

def main():
    if len(sys.argv) < 2:
        print("Usage: python image_to_bitmap.py <image_path> [width] [height]")
        sys.exit(1)

    # Get the image path from the command-line argument
    image_path = sys.argv[1]

    # Get width and height, or use defaults (16, 16)
    target_width = int(sys.argv[2]) if len(sys.argv) > 2 else 16
    target_height = int(sys.argv[3]) if len(sys.argv) > 3 else 16

    # Generate the output file name based on the image name
    output_file = os.path.splitext(os.path.basename(image_path))[0] + ".h"

    # Generate bitmap data
    bitmap_data = generate_bitmap_data(image_path, target_width, target_height)
    if bitmap_data:
        # Save the bitmap data to a header file
        save_bitmap_data(bitmap_data, target_width, target_height, output_file)

if __name__ == "__main__":
    main()
