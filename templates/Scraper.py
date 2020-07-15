import requests
from bs4 import BeautifulSoup
from Products import SProduct

# Request header
HEADERS = {'User-Agent': 'Mozilla/5.0'}


# Return the url of the product (from unique identifier)
def get_product_from_ui(ui, region):

    # Build the item url
    url = f"https://www.amazon.{region}/dp/{ui}"

    raw_html = requests.get(url, headers=HEADERS).text

    bs_object = BeautifulSoup(raw_html, "lxml")

    center_data = bs_object.find(id="centerCol")
    left_data = bs_object.find(id="leftCol")
    right_data = bs_object.find(id="rightCol")

    title = get_title(center_data)
    price = get_price(center_data)
    availability = get_availability(right_data)
    image_link = get_image(left_data)

    return SProduct(ui, title, price, availability, image_link)


# Return the title of the product
def get_title(bs_object):
    try:
        title = bs_object.find(id="productTitle").text.strip()
    except (AttributeError, KeyError):
        title = "Not available"

    return title


# Return the price of the product
def get_price(bs_object, price=None):
    try:
        price = bs_object.find(id="priceblock_ourprice").text.strip()
    except (AttributeError, KeyError):
        pass

    try:
        price = bs_object.find(id="priceblock_dealprice").text.strip()
    except (AttributeError, KeyError):
        pass

    if price is None:
        price = "Not available"

    return price


# Return the image link of the product
def get_availability(bs_object):
    try:
        availability = bs_object.find(id="availability").find("span").text.strip()
    except (AttributeError, KeyError):
        availability = "Not available"

    return availability


# Return the image link of the product
def get_image(bs_object):
    try:
        image_link = bs_object.find("div", {"class": "imgTagWrapper"}).find("img")['data-a-dynamic-image'].split('\"')[1]
    except (AttributeError, KeyError):
        image_link = "Not available"

    return image_link

