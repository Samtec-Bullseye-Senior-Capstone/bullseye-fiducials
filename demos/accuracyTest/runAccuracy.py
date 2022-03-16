import sys, csv, os
import argparse
import json
import cv2
from math import sqrt
from demos.accuracyTest.blobDetector import BlobDetector
from demos.accuracyTest.patternDetection import PatternDetector

blob_detector = BlobDetector()
pattern_detector = PatternDetector()
detectors = [
    ("BlobDetector", BlobDetector),
    ("PatternDetector", PatternDetector)
]


def draw_results(image, blobs):
    overlay = image.copy()
    for blob in blobs:
        cv2.circle(overlay, (int(blob["center_x"]), int(blob["center_y"])), int(blob["size"] / 2), (0, 0, 255), 2)
        cv2.line(overlay, (int(blob["center_x"]) - 20, int(blob["center_y"])),
                 (int(blob["center_x"]) + 20, int(blob["center_y"])), (0, 0, 255), 1)
        cv2.line(overlay, (int(blob["center_x"]), int(blob["center_y"]) - 20),
                 (int(blob["center_x"]), int(blob["center_y"]) + 20), (0, 0, 255), 1)
    return overlay


def draw_truths(image, blobs):
    overlay = image.copy()
    for blob in blobs:
        cv2.circle(overlay, (int(blob["center_x"]), int(blob["center_y"])), int(blob["size"] / 2), (0, 255, 0), 2)
        cv2.line(overlay, (int(blob["center_x"]) - 20, int(blob["center_y"])),
                 (int(blob["center_x"]) + 20, int(blob["center_y"])), (0, 255, 0), 1)
        cv2.line(overlay, (int(blob["center_x"]), int(blob["center_y"]) - 20),
                 (int(blob["center_x"]), int(blob["center_y"]) + 20), (0, 255, 0), 1)
    return overlay


def arg_parse():
    parser = argparse.ArgumentParser()
    parser.add_argument("-d", "--directory", default=None,
                        help="Directory of png images to run detection on.")
    parser.add_argument("-g", "--ground_truth", default=None,
                        help="Ground truth JSON file for the images.")
    parser.add_argument("-o", "--output", default=None,
                        help="JSON file to write results to.")
    parser.add_argument("-O", "--output_dir", default=None,
                        help="Director to output marked images.")
    args = parser.parse_args()
    if not args.directory:
        print("Please provide a directory of images.")
        parser.print_help()
    return args


def get_images(directory):
    files = os.listdir(directory)
    images = []
    for file in files:
        if file.endswith("png"):
            images.append((file, os.path.join(directory, file)))
    return images


def get_ground_truth(file):
    gt = None
    with open(file, "r") as f:
        gt = json.load(f)
    change = False
    for image in gt:
        for fid in gt[image]:
            if "center_x" not in fid:
                fid["center_x"] = fid["topLeft_x"] + (fid["size"] / 2)
                fid["center_y"] = fid["topLeft_y"] + (fid["size"] / 2)
                change = True
    if change:
        with open(file, "w") as f:
            json.dump(gt, f, indent=4)
    return gt


def write_output_images(images, results, output_dir):
    for tup in detectors:
        name, detector = tup
        if not os.path.isdir(output_dir):
            os.mkdir(output_dir)
        for image_tup in images:
            image_name, image_path = image_tup
            image = cv2.imread(image_path)
            # image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
            image = draw_results(image, results[name][image_name]["detector_results"])
            if "ground_truth" in results[name][image_name]:
                image = draw_truths(image, results[name][image_name]["ground_truth"])
            cv2.imwrite(os.path.join(output_dir, str(name) + str(image_name)), image)


def compute_distance(x1, y1, x2, y2):
    return sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2)


def compute_accuracy(results):
    for detector in results:
        all_accuracies = []
        missed = 0
        for image in results[detector]:
            if "detector_results" in results[detector][image] and "ground_truth" in results[detector][image]:
                accuracies = []
                for truth in results[detector][image]["ground_truth"]:
                    accuracy = None
                    for result in results[detector][image]["detector_results"]:
                        distance = compute_distance(truth["center_x"],
                                                    truth["center_y"],
                                                    result["center_x"],
                                                    result["center_y"])
                        if not accuracy:
                            accuracy = distance
                        else:
                            accuracy = min([accuracy, distance])
                    if accuracy:
                        accuracies.append(accuracy)
                    else:
                        missed += 1
                results[detector][image]["accuracy"] = accuracies
                all_accuracies.extend(accuracies)
        if all_accuracies:
            print(f"Accuracies: {all_accuracies}")
            results[detector]["all_accuracies"] = all_accuracies
            results[detector]["avg_accuracy"] = sum(all_accuracies) / len(all_accuracies)
            results[detector]["missed_detections"] = missed
    return results


def main(args):
    images = get_images(args.directory)
    ground_truth = None
    if args.ground_truth:
        ground_truth = get_ground_truth(args.ground_truth)
    results = {}
    for tup in detectors:
        name, detector_type = tup
        results[name] = {}
        for image_tup in images:
            image_name, image_path = image_tup
            print(f"Doing {name} detection on {image_name}... ", end="", flush=True)
            detector = detector_type(fid_size_px=ground_truth[image_name][0]['size']) \
                if image_name in ground_truth else detector_type()
            results[name][image_name] = {"detector_results": detector.detect(image_path)}
            if image_name in ground_truth:
                results[name][image_name]["ground_truth"] = ground_truth[image_name]
            print("Done!")
    if args.output:
        with open(args.output, "w") as f:
            f.write(json.dumps(results, indent=4))
    if args.output_dir:
        write_output_images(images, results, args.output_dir)

    results = compute_accuracy(results)

    print("Results:")
    print(json.dumps(results, indent=4))
    print("Summary:")
    for tup in detectors:
        name, detector = tup
        print(f"\t{name}:")
        print(f"\t\tAvg. Accuracy: {results[name]['avg_accuracy']}")
        print(f"\t\tMissed Detections: {results[name]['missed_detections']}")


if __name__ == "__main__":
    main(arg_parse())
