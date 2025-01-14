class MultiPartVersion:
    def __init__(self, parts, prefix=""):
        self.parts = parts
        self.prefix = prefix

    def prefixed_parts(self):
        """
        Prepends the first element of the version list
        with the prefix string.
        """
        if self.parts:
            return [self.prefix + str(self.parts[0])] + [str(part) for part in self.parts[1:]]
        else:
            return [self.prefix]

    def render_dots(self):
        return ".".join(self.prefixed_parts())

    def render_dots_or_parts(self, with_dots):
        if with_dots:
            return [self.render_dots()]
        else:
            return self.prefixed_parts()


class CudaVersion(MultiPartVersion):
    def __init__(self, major, minor):
        self.major = major
        self.minor = minor

        super().__init__([self.major, self.minor], "cuda")

    def __str__(self):
        return f"{self.major}.{self.minor}"
