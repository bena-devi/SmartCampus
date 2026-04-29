document.getElementById("registerForm").addEventListener("submit", function(e) {
    e.preventDefault();

    let name = document.getElementById("name").value;
    let email = document.getElementById("email").value;
    let username = document.getElementById("username").value;
    let password = document.getElementById("password").value;
    let confirmPassword = document.getElementById("confirmPassword").value;
    let message = document.getElementById("message");

    if (password !== confirmPassword) {
        message.style.color = "red";
        message.textContent = "Passwords do not match!";
        return;
    }

    // save user in localstorage
    let user = {
        name: name,
        email: email,
        username: username,
        password: password
    };

    localStorage.setItem("user", JSON.stringify(user));

    message.style.color = "green";
    message.textContent = "Registration Successful!";

    setTimeout(() => {
        window.location.href = "login.html";
    }, 1500);
});

function goToLogin() {
    window.location.href = "login.html";
}