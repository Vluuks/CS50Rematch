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
        self.items.append(item)

    # remove an item from the list, if you have it
    def remove(self, item):
        if item in self.items:
            self.items.remove(item)

    # checks whether the inventory contains an item by a certain name
    def contains(self, item_name):

        for item in self.items:
            if item.name.strip() == item_name.upper().strip():
                return True
        return False