class Item(object):
    """
    Representation of an item in adventure
    """

    def __init__(self, name, description, room_id):
        """
        Initialize an Item
        contains name, description and initial room where it can be found
        """

        # set variables
        self.name = name
        self.description = description
        self.room_id = room_id

    def __str__(self):
        return f"{self.name} {self.description}"