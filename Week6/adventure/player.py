class Player(object):
    """
    Representation of a player in Adventure
    """

    def __init__(self, id, name, room):
        """
        Initialize a Player with an id and name.
        """
        self.id = id
        self.name = name
        self.current_room = room

    def move(self, command):
        """
        Go to the next room based on command
        Takes in a text based command, i.e. "WEST" or "IN" or "EAST"
        Returns the room (a Room object) connected to said command
        Returns None if the command does not exist
        """
        # TODO
        pass

    def inventory(self):
        """
        Display the players current inventory.
        Either print it here or give back the required string, just make
        sure it is printed correctly.
        """
        # TODO
        pass

    def take(self, item_name):
        """
        Let the player take an item from their current location.
        Takes in a text based item name, i.e. "KEYS"
        Moves the item object from one inventory to the other.
        Returns a warning and does nothing for non-existant items.
        """
        # TODO
        pass

    def drop(self, item_name):
        """
        Let the player drop an item at their current location.
        Takes in a text based item name, i.e. "KEYS"
        Moves the item object from one inventory to the other.
        Returns a warning and does nothing for non-existant items.
        """
        # TODO
        pass