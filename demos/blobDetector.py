#!/usr/bin/env python3

import cv2
import sys
import numpy as np
import argparse, math


# help descriptions from: 
# https://docs.opencv.org/3.4/d0/d7a/classcv_1_1SimpleBlobDetector.html
# good visualization here:
# https://learnopencv.com/blob-detection-using-opencv-python-c/
def arg_parse():
    parser = argparse.ArgumentParser()
    parser.add_argument("-i", "--input_image", required=True)

    # filter by area
    parser.add_argument("--filterByArea", default=True, action='store_true', help="Extracted blobs have an area between minArea (inclusive) and maxArea (exclusive).")
    parser.add_argument('--minArea', type=int, default=300)
    parser.add_argument("--maxArea", type=int, default=4000)

    # filter by circularity
    parser.add_argument("--filterByCircularity", default=False, action='store_true', help="Extracted blobs have circularity ((4*pi*Area)/(perimiter**2)) between minCircularity (inclusive) and maxCircularity (exclusive).")
    parser.add_argument('--minCircularity', type=float, default=0.7)
    parser.add_argument('--maxCircularity', type=float)

    # filter by convexity
    parser.add_argument("--filterByConvexity", default=False, action='store_true', help="Extracted blobs have convexity (area / area of blob convex hull) between minConvexity (inclusive) and maxConvexity (exclusive).")
    parser.add_argument('--minConvexity', type=float)
    parser.add_argument('--maxConvexity', type=float)

    # filter by color
    parser.add_argument("--filterByColor", default=False, action='store_true', help="This filter compares the intensity of a binary image at the center of a blob to blobColor. If they differ, the blob is filtered out. Use blobColor = 0 to extract dark blobs and blobColor = 255 to extract light blobs.")
    parser.add_argument("--blobColor", type=int)

    # filter by inertia
    parser.add_argument("--filterByInertia", default=False, action='store_true', help="Extracted blobs have this ratio between minInertiaRatio (inclusive) and maxInertiaRatio (exclusive).")
    parser.add_argument("--minInertiaRatio", type=float, default=0.9)
    parser.add_argument("--maxInertiaRatio", type=float)

    # my configs:
    parser.add_argument("-a", "--show_area", default=False,  action='store_true', help="Draw the area of each keypoint at it's origin.")
    parser.add_argument("-o", "--output_image", default="", help="Image to output drawn keypoints to.")
    parser.add_argument("--dont_show", help="Don't bring up a window with the drawn output.")
    
    return parser.parse_args()

def get_params(args):
    params = cv2.SimpleBlobDetector_Params()
    # filter by area
    if args.filterByArea:
        params.filterByArea = args.filterByArea
        if args.minArea: params.minArea = args.minArea
        if args.maxArea: params.maxArea = args.maxArea
    if args.filterByCircularity:
        params.filterByCircularity = args.filterByCircularity
        if args.minCircularity: params.minCircularity = args.minCircularity
        if args.maxCircularity: params.maxCircularity = args.maxCircularity
    if args.filterByConvexity:
        params.filterByConvexity = args.filterByConvexity
        if args.minConvexity: params.minConvexity = args.minConvexity
        if args.maxConvexity: params.maxConvexity = args.maxConvexity
    if args.filterByInertia:
        params.filterByInertia = args.filterByInertia
        if args.minInertiaRatio: params.minInertiaRatio = args.minInertiaRatio
        if args.maxInertiaRatio: params.maxInertiaRatio = args.maxInertiaRatio
    return params

def main(args, params):
    if not str(args.input_image).endswith(".png") and not str(args.input_image).endswith(".jpg"):
        print(f"Invalid file type: {input_image}")
        sys.exit(1)

    image = cv2.imread(args.input_image)
    overlay = image.copy()
    detector = cv2.SimpleBlobDetector_create(params)
    keypoints = detector.detect(image)
    for k in keypoints:
        cv2.circle(overlay, (int(k.pt[0]), int(k.pt[1])), int(k.size/2), (0, 0, 255), -1)
        cv2.line(overlay, (int(k.pt[0])-20, int(k.pt[1])), (int(k.pt[0])+20, int(k.pt[1])), (0,0,0), 3)
        cv2.line(overlay, (int(k.pt[0]), int(k.pt[1])-20), (int(k.pt[0]), int(k.pt[1])+20), (0,0,0), 3)
        if args.show_area:
            cv2.putText(overlay, f"{math.pi*((k.size/2)**2)}", (int(k.pt[0]), int(k.pt[1])), cv2.FONT_HERSHEY_SIMPLEX, 1, (255,0,0), 2, cv2.LINE_AA)
    opacity = 0.5
    cv2.addWeighted(overlay, opacity, image, 1-opacity, 0, image)

    if not args.dont_show:
        cv2.namedWindow("Output", cv2.WINDOW_NORMAL)
        cv2.imshow(f"Output", overlay)
        cv2.waitKey(0)
        cv2.destroyAllWindows()
    if len(args.output_image) > 0:
        cv2.imwrite(args.output_image, overlay)

if __name__ == "__main__":
    args = arg_parse()
    print(args)
    main(args, get_params(args))
