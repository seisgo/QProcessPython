import sys
sys.path.append('/usr/local/anaconda3/lib/python3.6/site-packages')
print(sys.path, flush=True)

import tensorflow as tf
import argparse as ap

tf.flags.DEFINE_enum('output_color', 'GRAY', ('RGB', 'L', 'GRAY', 'Y'), help="specify output color format")
tf.flags.DEFINE_integer('epochs', 100, lower_bound=1, help="training epochs")

parser = ap.ArgumentParser(description='Testing argparse')
parser.add_argument('color', type=str)

def addv(a, b):
    return a+b

if __name__ == "__main__":
    print("Main program is running...", flush=True)
    a = 4
    b = 3
    print("%d + %d = %d" %(a, b, addv(a, b)), flush=True)
