
class SProduct:
    def __init__(self, ui, title, price, availability, image_link):
        self.ui = ui
        self.title = title
        self.price = price
        self.availability = availability
        self.image_link = image_link

    def get_price(self):
        return self.price

    def export_product(self):
        return self

    def print(self):
        print("UI: {0}".format(self.ui))
        print("Title: {0}".format(self.title))
        print("Price: {0}".format(self.price))
        print("Availability: {0}".format(self.availability))
        print("Image Link: {0}".format(self.image_link))
