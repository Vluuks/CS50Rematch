class Room(object):
    """
    Representation of a room in Adventure
    """

    def __init__(self, id, name, description, options, options_dict, options_set):
        """
        Initialize a Room
        give it an id, name and description
        the items present in the room will be added later on
        """
        # set variables
        self.id = id
        self.name = name
        self.description = description
        self.options = options
        self.options_dict = options_dict
        self.options_set = options_set
        self.items = []