import pandas as pd
import random
from faker import Faker

# Initialize Faker for generating fake data
fake = Faker()

# Generate sample data
num_entries = 100
data = {
    "ID": [i + 1 for i in range(num_entries)],
    "Name": [fake.name() for _ in range(num_entries)],
    "Email": [fake.email() for _ in range(num_entries)],
    "Age": [random.randint(18, 70) for _ in range(num_entries)],
    "City": [fake.city() for _ in range(num_entries)],
    "JoinDate": [fake.date_between(start_date='-5y', end_date='today') for _ in range(num_entries)]
}

# Create a DataFrame
df = pd.DataFrame(data)

# Save to CSV
df.to_csv("sample_data.csv", index=False)

print("CSV file 'sample_data.csv' has been created.")
