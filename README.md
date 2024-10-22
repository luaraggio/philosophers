<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="description" content="Philosophers Simulation in C using Threads and Processes.">
</head>
<body>

<h1>Philosophers - A Synchronization Problem</h1>

<p>
    Welcome to the <strong>Philosophers Simulation</strong> project. This is a classic concurrency problem solved using <strong>threads</strong> and <strong>mutexes</strong> in the mandatory part and <strong>processes</strong> and <strong>semaphores</strong> in the bonus part. The goal is to simulate a group of philosophers who alternate between eating, thinking, and sleeping while competing for limited resources (forks) at a table.
</p>

<h2>Table of Contents</h2>
<ul>
    <li><a href="#overview">Overview</a></li>
    <li><a href="#global-rules">Global Rules</a></li>
    <li><a href="#program-arguments">Program Arguments</a></li>
    <li><a href="#logs">Logs</a></li>
    <li><a href="#mandatory-part">Mandatory Part</a></li>
    <li><a href="#bonus-part">Bonus Part</a></li>
    <li><a href="#compilation-and-execution">Compilation and Execution</a></li>
    <li><a href="#external-functions">External Functions</a></li>
</ul>

<h2 id="overview">Overview</h2>
<p>
    In this project, philosophers sit at a round table with a bowl of spaghetti in the center. They take turns eating, thinking, and sleeping. However, they can only eat if they hold both a fork on their right and left hand. After eating, they sleep, and once awake, they start thinking again. The simulation stops when a philosopher dies from starvation, and the goal is to ensure that no philosopher starves.
</p>
<p>
    The project aims to model the philosophers' behavior, focusing on concurrency and synchronization mechanisms to avoid issues such as deadlock (when philosophers are unable to proceed because they are waiting for forks) and data races (conflicting access to shared resources). The simulation must be able to handle multiple philosophers without any race conditions.
</p>

<h2 id="global-rules">Global Rules</h2>
<ul>
    <li>Global variables are strictly forbidden.</li>
    <li>The program must accept the following arguments:
        <ul>
            <li><strong>number_of_philosophers</strong>: Number of philosophers and forks.</li>
            <li><strong>time_to_die</strong>: Time in milliseconds before a philosopher dies if they don’t start eating.</li>
            <li><strong>time_to_eat</strong>: Time in milliseconds a philosopher spends eating.</li>
            <li><strong>time_to_sleep</strong>: Time in milliseconds a philosopher spends sleeping.</li>
            <li><strong>number_of_times_each_philosopher_must_eat</strong>: (Optional) The number of times each philosopher must eat before the simulation stops.</li>
        </ul>
    </li>
    <li>Each philosopher is identified by a number ranging from 1 to <em>number_of_philosophers</em>.</li>
    <li>The first philosopher sits next to the last one, forming a circular arrangement.</li>
    <li>Philosophers cannot communicate with each other or know if another is about to die.</li>
    <li>Time is measured in milliseconds, and precise control is required to ensure correct behavior.</li>
</ul>

<h2 id="program-arguments">Program Arguments</h2>
<p>
    The program accepts the following arguments:
</p>
<ul>
    <li><strong>number_of_philosophers</strong>: Number of philosophers at the table. Also corresponds to the number of forks.</li>
    <li><strong>time_to_die</strong>: Time in milliseconds before a philosopher dies if they don’t start eating.</li>
    <li><strong>time_to_eat</strong>: Time a philosopher spends eating.</li>
    <li><strong>time_to_sleep</strong>: Time a philosopher spends sleeping.</li>
    <li><strong>number_of_times_each_philosopher_must_eat</strong> (optional): If all philosophers have eaten this number of times, the simulation ends.</li>
</ul>

<h2 id="logs">Logs</h2>
<p>
    The state of each philosopher must be logged according to the following format:
</p>
<ul>
    <li><strong>timestamp_in_ms X has taken a fork</strong></li>
    <li><strong>timestamp_in_ms X is eating</strong></li>
    <li><strong>timestamp_in_ms X is sleeping</strong></li>
    <li><strong>timestamp_in_ms X is thinking</strong></li>
    <li><strong>timestamp_in_ms X died</strong></li>
</ul>
<p>
    These logs must be printed in real-time, and no messages should overlap. A message indicating the death of a philosopher should appear within 10 milliseconds after the event.
</p>

<h2 id="mandatory-part">Mandatory Part</h2>
<p>
    In the mandatory part, each philosopher is represented by a <strong>thread</strong>, and forks are shared between philosophers using <strong>mutexes</strong> to prevent race conditions. The simulation must handle concurrent access to shared resources correctly.
</p>
<ul>
    <li>Each philosopher is implemented as a thread.</li>
    <li>A mutex protects each fork, preventing two philosophers from using the same fork at the same time.</li>
    <li>There is one fork between each pair of philosophers, and a philosopher must pick up both the left and right fork before eating.</li>
</ul>

<h2 id="bonus-part">Bonus Part</h2>
<p>
    The bonus part uses <strong>processes</strong> instead of threads and <strong>semaphores</strong> to manage the shared resources (forks). Here, each philosopher is a separate process, and a semaphore represents the number of available forks.
</p>
<ul>
    <li>Each philosopher is represented by a process.</li>
    <li>The number of available forks is controlled by a semaphore.</li>
    <li>Processes must synchronize correctly to avoid deadlock and starvation.</li>
</ul>

<h2 id="compilation-and-execution">Compilation and Execution</h2>
<p>
    To compile the project, navigate to the project directory and run the following command:
</p>
<pre><code>make</code></pre>
<p>
    This will generate the executable <code>philo</code> for the mandatory part and <code>philo_bonus</code> for the bonus part (if implemented). To run the simulation, execute:
</p>
<pre><code>./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]</code></pre>
<p>
    Example:
</p>
<pre><code>./philo 5 800 200 200</code></pre>
<p>
    This runs the simulation with 5 philosophers, where each philosopher dies after 800 milliseconds without eating, takes 200 milliseconds to eat, and 200 milliseconds to sleep.
</p>

<h2 id="external-functions">External Functions</h2>
<p>
    The following external functions are used in this project:
</p>
<ul>
    <li><strong>memset</strong></li>
    <li><strong>printf</strong></li>
    <li><strong>malloc</strong></li>
    <li><strong>free</strong></li>
    <li><strong>write</strong></li>
    <li><strong>usleep</strong></li>
    <li><strong>gettimeofday</strong></li>
    <li><strong>pthread_create</strong></li>
    <li><strong>pthread_detach</strong></li>
    <li><strong>pthread_join</strong></li>
    <li><strong>pthread_mutex_init</strong></li>
    <li><strong>pthread_mutex_destroy</strong></li>
    <li><strong>pthread_mutex_lock</strong></li>
    <li><strong>pthread_mutex_unlock</strong></li>
    <li>For the bonus part: <strong>fork, kill, exit, sem_open, sem_close, sem_post, sem_wait, sem_unlink</strong></li>
</ul>

</body>
</html>
