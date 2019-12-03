fps_data = []
num_particles_data = []

with open("data/fps_data.txt", "r") as f:
    all_lines = f.readlines();
    # print("number of lines: " + str(len(all_lines)))
    for fps_pair in all_lines:
        fps_list = fps_pair.split(", ")
        num_particles = int(fps_list[0])
        fps = float(fps_list[1][:-1])
        # print(num_particles)
        # print(fps)
        num_particles_data.append(num_particles)
        fps_data.append(fps)

import matplotlib.pyplot as plt

nlist = range(1, len(fps_data)+1)

plt.subplot(211)
plt.plot(nlist, fps_data)
plt.title("FPS Variation")
plt.xlabel("the Frame No.")
plt.ylabel("Frames per Second")
plt.subplot(212)
plt.plot(nlist, num_particles_data, color='orange')
plt.title("Number of Particles Variation")
plt.xlabel("the Frame No.")
plt.ylabel("Number of Particles")

plt.show()

