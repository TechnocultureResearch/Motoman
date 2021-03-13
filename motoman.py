import motors_manager

def main():
  print(motors_manager.add(2, 5))
  print("main")

if __name__ == "__main__":
  import os, sys
  sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), ".")))
  main()
