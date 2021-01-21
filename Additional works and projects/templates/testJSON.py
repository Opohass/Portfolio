import json
import Scraper
import Products

data = Scraper.get_product_from_ui("B00D89VK3Q", "com")
product_json = {"Ui": [data.ui], "Title": [data.title], "Price": [data.price], "Availability": [data.availability], "Image_link": [data.image_link]}

print(product_json)

with open("product_data.json", "r") as read_file:
    prod_json_main = json.load(read_file)

print(prod_json_main["Ui"])

if product_json["Title"] == product_json["Price"]:
    print("Error occurred while collecting product data")

else:
    prod_json_main["Ui"] += product_json["Ui"]
    prod_json_main["Title"] += product_json["Title"]
    prod_json_main["Price"] += product_json["Price"]
    prod_json_main["Availability"] += product_json["Availability"]
    prod_json_main["Image_link"] += product_json["Image_link"]

print(len(prod_json_main["Ui"]))

with open("product_data.json", "w") as write_file:
    json.dump(prod_json_main, write_file, indent=4)
