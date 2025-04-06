"""
Second Update for the project of web search application using basic python. 

"""

movies = ["The Shawshank Redemption", "The Godfather", "The Dark Knight", "Forrest Gump", "Inception", "The Matrix", "Avengers: Infinity War", "Back to the Future", "The Lion King", "Pulp Fiction"]
matching=[]
history={}

while True:
    movie_name=input("Input the movie that you want to look for: ").lower()
    if movie_name=="last":
        print(f"Search history: {history}")
    elif movie_name=="exit":
        print("See you again!")
        break
    else:
        history.clear()
        matching.clear()
        movie_name_new = movie_name.split()
        for movie in movies:
            if any(term in movie.lower().split() for term in movie_name_new):
                matching.append(movie)

        length=len(matching)
        history[movie_name] = matching

        if length==0:
            print(f"{length} matching movies found.")
            print("No results found!")


        else:
            print(f"{length} matching movies found.")
            for i in matching:
                print(i)
        
    




