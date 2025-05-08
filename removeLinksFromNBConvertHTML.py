# coding: utf-8
import argparse
import os
import sys
from bs4 import BeautifulSoup

def parse_file(input_filename):
    if not os.path.isfile(input_filename):
        raise argparse.ArgumentTypeError("File does not exist. Please use a valid file path.")
    return(input_filename)

parser=argparse.ArgumentParser(description="Script to remove all Hyperlinks from HTML nbconvert of our Jupyter Notebooks")
parser.add_argument("FILENAME",help="HTML File you want to remove all Hyperlinks from.", type=parse_file)
args=parser.parse_args()
print(args)
filename=args.FILENAME

# Open and read the HTML file
with open(filename, "r",encoding="utf8") as file:
    html_content = file.read()

# Create a BeautifulSoup object
soup = BeautifulSoup(html_content, "html.parser")

# Find all div elements with class 'jp-CodeMirrorEditor'
video_cells = soup.find_all('div', class_='jp-CodeMirrorEditor')
    
# Iterate through cells and remove those containing video elements
for cell in video_cells:
    if cell.find('video') or '%%HTML' in cell.text:
        cell.decompose()

# Remove iframe containers
iframes = soup.find_all('iframe')
for iframe in iframes:
    iframe.decompose()

for a in soup.find_all('a'):
    text = a.string
    if text:
        if text.endswith('¶'):
            new_text = text[:-1]  # Remove the last character if it's a period
        else:
            new_text = text  # Keep the text as is if it doesn't end with a period
        a.string.replace_with(new_text)
    a.unwrap()

text_to_remove="https://www.pygame.org/contribute.html"
for element in soup.find_all(text=True):
        if text_to_remove in element:
            # Replace the text with empty string
            element.replace_with(element.replace(text_to_remove, ''))

modified_html=str(soup)

# Save the modified HTML to a new file
with open(filename, 'w',encoding="utf8") as file:
    file.write(modified_html)