import subprocess
import pandas as pd
import matplotlib.pyplot as plt


def get_nearest(lat, lon):
    result = subprocess.run(
        ["./build/nearest_neighbor", str(lat), str(lon)],
        capture_output=True, text=True
    )
    return eval(result.stdout.strip())


# Get user input
user_lat = input("Enter your latitude: ")
user_lon = input("Enter your longitude: ")
# using default values if no input is provided
if user_lat == "" and user_lon == "":
    user_lat = 3
    user_lon = 4
else:
    user_lat = float(user_lat)
    user_lon = float(user_lon)

# Call C backend
nearest = get_nearest(user_lat, user_lon)

# Load data
df = pd.read_csv("data/zomato_locations.csv")

# Setup plot
plt.figure(figsize=(10, 8))

# Plot restaurants with names
for _, row in df.iterrows():
    if row['Name'] == nearest['name']:
        plt.scatter(row['lon'], row['lat'], c='red',
                    s=50, label='Destination (Nearest)')
    else:
        plt.scatter(row['lon'], row['lat'], c='green', s=50)
    plt.annotate(row['Name'], (row['lon'], row['lat']), xytext=(0, 5),
                 textcoords='offset points', ha='center', fontsize=8, color='black')

# Plot user location
plt.scatter(user_lon, user_lat, label='You (User)',
            c='blue', s=100, marker='X')

# Line between user and nearest
plt.plot([user_lon, nearest['lon']], [user_lat, nearest['lat']],
         'k--', label='Distance Line')

# Title and decorations
plt.title("Nearest Restaurant to Your Location")
plt.xlabel("Longitude")
plt.ylabel("Latitude")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig("output/nearest_restaurant_map.png", dpi=400)
plt.show()
