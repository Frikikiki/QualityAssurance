import requests
from bs4 import BeautifulSoup
from urllib.parse import urljoin, urlparse
import datetime

forbidden_prefixes = ['#', 'tel://', 'mailto:']
file_broken = open("broken_links.txt", "w")
file_valid = open("valid_links.txt", "w")
valid_links = []
broken_links = []
now_data = datetime.datetime.now()

URL = "http://52.136.215.164/broken-links/"


def get_host(url):
    return '{url.scheme}://{url.netloc}/'.format(url=urlparse(url))


def get_status_code(url):
    return requests.head(url).status_code


def is_url_ok(status_code):
    return status_code == 200


def print_data(output_file, links_count, data):
    output_file.write("Links count: " + str(links_count) + "\n")
    output_file.write("Date of the test: " + str(data.day) + "-" +
                     str(data.month) + "-" + str(data.year))


def get_new_links(valid_links, broken_links, url):
    x = requests.get(url)
    soup = BeautifulSoup(x.text, features="html.parser")
    links = soup.findAll('a', href=True)
    for link in links:
        if any(link.get("href").startswith(prefix) for prefix in forbidden_prefixes):
            continue
        next_url = urljoin(url, link.get("href"))
        if next_url in valid_links or next_url in broken_links:
            continue
        status_code = get_status_code(next_url)
        if is_url_ok(status_code):
            file_valid.write(next_url + " - " + str(status_code) + " \n")
            valid_links.append(next_url)
            if get_host(next_url) == get_host(URL):
                get_new_links(valid_links, broken_links, next_url)
        else:
            file_broken.write(next_url + " - " + str(status_code) + " \n")
            broken_links.append(next_url)


get_new_links(valid_links, broken_links, URL)
print_data(file_valid, len(valid_links), now_data)
print_data(file_broken, len(broken_links), now_data)
