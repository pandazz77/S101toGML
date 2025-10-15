from osgeo import ogr
import json

def diff_dicts(dict1, dict2):
    """Print differences between two dictionaries"""
    print("Differences:")
    
    # Keys in dict1 but not in dict2
    for key in dict1:
        if key not in dict2:
            print(f"Key '{key}' only in dict1: {dict1[key]}")
    
    # Keys in dict2 but not in dict1
    for key in dict2:
        if key not in dict1:
            print(f"Key '{key}' only in dict2: {dict2[key]}")
    
    # Keys in both, but different values
    for key in dict1:
        if key in dict2 and dict1[key] != dict2[key]:
            print(f"Key '{key}': dict1={dict1[key]}, dict2={dict2[key]}")

def get_sorted_features(layer, sort_field='gml_id'):
    """Get features sorted by the specified field"""
    features = []
    
    # Read all features
    layer.ResetReading()
    for feature in layer:
        features.append(feature)
    
    # Sort features by the specified field
    try:
        features.sort(key=lambda x: x.GetField(sort_field) or '')
    except Exception as e:
        print(f"Warning: Could not sort by field '{sort_field}': {e}")
        print("Available fields:", [field.GetName() for field in layer.schema])
        # Sort by FID as fallback
        features.sort(key=lambda x: x.GetFID())
    
    return features

def compare_gml_files(file1, file2, sort_field='gml_id'):
    # Open both files
    ds1 = ogr.Open(file1)
    ds2 = ogr.Open(file2)
    
    if not ds1 or not ds2:
        print("Error: Could not open one or both files")
        return
    
    layer1 = ds1.GetLayer()
    layer2 = ds2.GetLayer()
    
    print(f"File1: {file1}")
    print(f"File2: {file2}")
    print(f"Layer1: {layer1.GetName()}")
    print(f"Layer2: {layer2.GetName()}")
    
    # Compare schema
    schema1 = [(field.GetName(), field.GetTypeName()) for field in layer1.schema]
    schema2 = [(field.GetName(), field.GetTypeName()) for field in layer2.schema]
    
    print("\n=== Schema Comparison ===")
    schema_diff = set(schema1) - set(schema2)
    if schema_diff:
        print("Schema differences (in file1 but not in file2):", schema_diff)
    else:
        print("Schemas are identical")
    
    schema_diff2 = set(schema2) - set(schema1)
    if schema_diff2:
        print("Schema differences (in file2 but not in file1):", schema_diff2)
    
    # Compare feature counts
    count1 = layer1.GetFeatureCount()
    count2 = layer2.GetFeatureCount()
    print(f"\n=== Feature Count ===")
    print(f"Features in file1: {count1}")
    print(f"Features in file2: {count2}")
    
    if count1 != count2:
        print("Warning: Different number of features!")
    
    # Get sorted features
    print(f"\n=== Sorting features by '{sort_field}' ===")
    features1 = get_sorted_features(layer1, sort_field)
    features2 = get_sorted_features(layer2, sort_field)
    
    print(f"Sorted {len(features1)} features from file1")
    print(f"Sorted {len(features2)} features from file2")
    
    # Compare features
    print(f"\n=== Feature Comparison ===")
    
    # Compare common features (minimum count)
    min_count = min(len(features1), len(features2))
    max_count = max(len(features1), len(features2))
    
    differences_found = 0
    
    for i in range(max_count):
        if i >= len(features1):
            print(f"Feature {i} only in file2 (gml_id: {features2[i].GetField(sort_field)})")
            continue
        elif i >= len(features2):
            print(f"Feature {i} only in file1 (gml_id: {features1[i].GetField(sort_field)})")
            continue
        
        f1 = features1[i]
        f2 = features2[i]
        
        # Get gml_id for reference
        gml_id1 = f1.GetField(sort_field)
        gml_id2 = f2.GetField(sort_field)
        
        f1_json = json.loads(f1.ExportToJson())
        f2_json = json.loads(f2.ExportToJson())
        
        if f1_json != f2_json:
            print(f"\nDifference found at position {i}")
            print(f"gml_id file1: {gml_id1}, gml_id file2: {gml_id2}")
            
            if gml_id1 != gml_id2:
                print(f"WARNING: Different gml_ids at same position: {gml_id1} vs {gml_id2}")
            
            print(f"Feature {i} differences:")
            diff_dicts(f1_json, f2_json)
            differences_found += 1
            
            # Ask if user wants to continue or stop after first difference
            # Uncomment the next line if you want to stop after first difference
            # break
    
    print(f"\nTotal differences found: {differences_found}")
    
    # Also check if any features are completely missing between files
    print(f"\n=== Checking for missing features ===")
    
    # Get all gml_ids from both files
    layer1.ResetReading()
    all_gml_ids_1 = set()
    for feature in layer1:
        gml_id = feature.GetField(sort_field)
        if gml_id:
            all_gml_ids_1.add(gml_id)
    
    layer2.ResetReading()
    all_gml_ids_2 = set()
    for feature in layer2:
        gml_id = feature.GetField(sort_field)
        if gml_id:
            all_gml_ids_2.add(gml_id)
    
    only_in_1 = all_gml_ids_1 - all_gml_ids_2
    only_in_2 = all_gml_ids_2 - all_gml_ids_1
    
    if only_in_1:
        print(f"Features only in file1: {sorted(only_in_1)}")
    if only_in_2:
        print(f"Features only in file2: {sorted(only_in_2)}")


import sys, os

if len(sys.argv) != 3:
    print(f"Usage: python {os.path.basename(__file__)} file1.gml file2.gml")
    sys.exit(1)

compare_gml_files(sys.argv[1], sys.argv[2])