import json

def load_json_to_dict(file_path):
    """Load JSON file and convert to dictionary"""
    try:
        with open(file_path, 'r') as file:
            data = json.load(file)
        return data
    except FileNotFoundError:
        print(f"Error: File '{file_path}' not found.")
        return None
    except json.JSONDecodeError:
        print(f"Error: Invalid JSON format in '{file_path}'.")
        return None

# Example usage
if __name__ == "__main__":
    # Load from file
    json_file = "duckhunt.json"
    dictionary = load_json_to_dict(json_file)
    
    if dictionary:
        print("JSON loaded successfully:")
        print(dictionary)
        print(f"Type: {type(dictionary)}")
        
        
    print(json.dumps(dictionary,indent=4))
