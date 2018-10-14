class Room(object):
    """
    Representation of a room in Adventure
    """

    def __init__(self, id, name, description, options):
        """
        Initialize a Room
        give it an id, name and description
        """
        # set variables
        self.id = id
        self.name = name
        self.description = description
        self.options = options