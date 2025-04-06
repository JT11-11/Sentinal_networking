import re

def searchresult(terms):
    criteria = {}
    result = []
    
    
    search = re.findall(r'(\w+):"([^"]+)"|(\w+):(\w+)', terms)


    for term in search:
        if term[0]:
            keys, values = term[0], term[1].lower()
        else:
            keys, values = term[2], term[3].lower()
        criteria[keys] = values

    for movie in movies:
        match = True
        for key, value in criteria.items():
            if key not in movie or value not in str(movie[key]).lower():
                match = False
                break
        if match:
            result.append(movie)

    return result

movies = [
    {"title": "The Shawshank Redemption", "director": "Frank Darabont", "year": 1994, "genre": "Drama"},
    {"title": "The Godfather", "director": "Francis Ford Coppola", "year": 1972, "genre": "Crime, Drama"},
    {"title": "The Dark Knight", "director": "Christopher Nolan", "year": 2008, "genre": "Action, Crime, Drama"},
    {"title": "Forrest Gump", "director": "Robert Zemeckis", "year": 1994, "genre": "Drama, Romance"},
    {"title": "Inception", "director": "Christopher Nolan", "year": 2010, "genre": "Action, Adventure, Sci-Fi"},
    {"title": "The Matrix", "director": "Lana Wachowski, Lilly Wachowski", "year": 1999, "genre": "Action, Sci-Fi"},
    {"title": "Avengers: Infinity War", "director": "Anthony Russo, Joe Russo", "year": 2018, "genre": "Action, Adventure, Sci-Fi"},
    {"title": "Back to the Future", "director": "Robert Zemeckis", "year": 1985, "genre": "Adventure, Comedy, Sci-Fi"},
    {"title": "The Lion King", "director": "Roger Allers, Rob Minkoff", "year": 1994, "genre": "Animation, Adventure, Drama"},
    {"title": "Pulp Fiction", "director": "Quentin Tarantino", "year": 1994, "genre": "Crime, Drama"},
    {"title": "Fight Club", "director": "David Fincher", "year": 1999, "genre": "Drama"},
    {"title": "Interstellar", "director": "Christopher Nolan", "year": 2014, "genre": "Adventure, Drama, Sci-Fi"},
    {"title": "Spirited Away", "director": "Hayao Miyazaki", "year": 2001, "genre": "Animation, Adventure, Family"},
    {"title": "La La Land", "director": "Damien Chazelle", "year": 2016, "genre": "Comedy, Drama, Music"},
    {"title": "Jurassic Park", "director": "Steven Spielberg", "year": 1993, "genre": "Action, Adventure, Sci-Fi"},
    {"title": "Titanic", "director": "James Cameron", "year": 1997, "genre": "Drama, Romance"},
    {"title": "The Lord of the Rings: The Fellowship of the Ring", "director": "Peter Jackson", "year": 2001, "genre": "Adventure, Drama, Fantasy"},
    {"title": "Star Wars: Episode IV - A New Hope", "director": "George Lucas", "year": 1977, "genre": "Action, Adventure, Fantasy"},
    {"title": "Goodfellas", "director": "Martin Scorsese", "year": 1990, "genre": "Biography, Crime, Drama"},
    {"title": "The Silence of the Lambs", "director": "Jonathan Demme", "year": 1991, "genre": "Crime, Drama, Thriller"},
]

terms = input('Enter search terms (e.g., director:"Robert Zemeckis" genre:Drama year:1994): ')
result = searchresult(terms)

if result:
    for movie in result:
        print(f"Title: {movie['title']}, Director: {movie['director']}, Year: {movie['year']}, Genre: {movie['genre']}")
else:
    print("No results found.")
