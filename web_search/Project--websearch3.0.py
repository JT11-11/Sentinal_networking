import csv


def searchmovies(search_field,search_term,lines):
    results=[]
    for movie in lines:
        if search_field in movie and search_term.lower() in str(movie[search_field]).lower():
            results.append(movie)
    return results




def load_movies(csv_file_path):
    with open(csv_file_path, 'r') as file:
        csv_reader = csv.DictReader(file)
        lines = []
        for line in csv_reader:
            lines.append(line)
    return lines



#csv_file_path = r'.csv'
#uncomment and fill in the csv file name. 

search_field=input("Enter yourr search field: ")
search_term=input("Enter your search term: ")
lines=load_movies(csv_file_path)
results=searchmovies(search_field,search_term,lines)

if results:
    for movie in results:
        print(f"title:{lines['title']},director:{lines['director']},year:{lines['year']},genre:{lines['genre']}")
else:
    print("No search result found! ")










