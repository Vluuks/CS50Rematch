class Inventory(object):
    """
    Representation of an item in adventure
    """

    def __init__(self):
        """
        Initialize an Inventory
        which contains a list of items
        """

        self.items = []

    # adds an item to your list
    def add(self, item):
        self.items.push(item)

    # remove an item from the list, if you have it
    def remove(self, item_name):
        if item_name in self.items:
            self.items.remove(item_name)