document.getElementById("loginForm").addEventListener("submit", function(e) {
    e.preventDefault();


    // Login Page
    let username = document.getElementById("username").value;
    let password = document.getElementById("password").value;
    let errorMsg = document.getElementById("errorMsg");

    
    let validUser = "admin";
    let validPass = "1234";


    if (username === validUser && password === validPass) {
        alert("Login Successful!");
        window.location.href = "dashboard.html";
    } else {
        errorMsg.textContent = "Invalid Username or Password";
    }
});

function goBack() {
    window.history.back();
}
