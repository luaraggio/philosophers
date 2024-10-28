<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="description" content="Philosophers Simulation in C using Threads and Processes.">
</head>
<body>

<h1>Philosophers - A Synchronization Problem 🍴</h1>

<p>
    This is a classic concurrency problem solved using <strong>threads</strong> and <strong>mutexes in C.</strong> The goal is to simulate a group of philosophers who alternate between eating, thinking, and sleeping while competing for limited resources (forks) at a table.
</p>
<br>
<p align="center">
  <img src="https://external-preview.redd.it/EdZBvHGbDaxNlNIB4Ui9KSLMRDM0c9eOMp8hZkc6_s0.jpg?width=640&crop=smart&auto=webp&s=0cf08975cc57702ebb71b979849ce52b901afdc7" alt="Descrição da imagem" width="500">
</p>
<h2 id="overview">Overview</h2>
<p>
    Philosophers sit at a round table with a bowl of spaghetti in the center.They take turns eating, sleeping and thinking. However, they can only eat if they hold both a fork on their right and left hand. After eating, they sleep, and once awake, they start thinking again. The simulation stops when a philosopher dies from starvation and the goal is to ensure that no philosopher starves.
</p>
<p>
    In this project, each philosopher is a thread and I have to use concurrency and synchronization mechanisms to avoid issues such as deadlock (when philosophers are unable to proceed because they are waiting for forks) and data races (conflicting access to shared resources in more than one thread).
</p>

<h2 id="program-arguments">Program Arguments</h2>
    <li><strong>number_of_philosophers</strong>: Number of philosophers at the table. Also corresponds to the number of forks.</li>
    <li><strong>time_to_die</strong>: Time in milliseconds before a philosopher dies if they don’t start eating.</li>
    <li><strong>time_to_eat</strong>: Time a philosopher spends eating.</li>
    <li><strong>time_to_sleep</strong>: Time a philosopher spends sleeping.</li>
    <li><strong>number_of_times_each_philosopher_must_eat</strong> (optional): If all philosophers have eaten this number of times, the simulation ends.</li>

<h2 id="logs">Logs in Real-Time</h2>
    <li><strong>timestamp_in_ms X has taken a fork</strong></li>
    <li><strong>timestamp_in_ms X is eating</strong></li>
    <li><strong>timestamp_in_ms X is sleeping</strong></li>
    <li><strong>timestamp_in_ms X is thinking</strong></li>
    <li><strong>timestamp_in_ms X died</strong></li>

<h2 id="compilation-and-execution">Compilation and Execution</h2>
<p>
    To compile the project, navigate to the project directory and run the following command:
</p>
<pre><code>make</code></pre>
<p>
    To run the simulation, execute:
</p>
<pre><code>./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]</code></pre>
<p>
    Such as:
</p>
<pre><code>./philo 5 800 200 200</code></pre>
<p>
    This means the simulation will have 5 philosophers, a philo dies after 800 milliseconds without eating, takes 200 milliseconds to eat, and 200 milliseconds to sleep.
</p>
<p>Enjoy testing different inputs and see what happens with each philosopher. What do you think? Will they🍴,😴, or ☠️?</p>

</body>
</html>
